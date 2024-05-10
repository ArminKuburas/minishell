/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini_split_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:14:46 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 14:19:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	quote_found(char *quote, char c)
{
	if (*quote == '\0')
		*quote = c;
	else if (*quote == c)
		*quote = '\0';
}

void	split_memory_failed(t_shelldata *data)
{
	ft_putstr_fd("bananashell: Memory allocation failed\n", 2);
	clear_input(data->input_list, FAILURE);
	free(data->input);
	clear_env_list(data->env_list, FAILURE);
	rl_clear_history();
	exit(1);
}

int	duplicate_input(char *input, t_shelldata *data, int *i)
{
	int		j;
	char	quote;

	quote = '\0';
	j = 0;
	while (input[j])
	{
		if (input[j] == '\'' || input[j] == '"')
			quote_found(&quote, input[j]);
		if (quote == '\0' && ft_strchr("<>| \t", input[j]))
			break ;
		j++;
	}
	if (quote != '\0')
	{
		ft_putstr_fd("Error: No closing quote found\n", 2);
		return (NO_QUOTE);
	}
	if (create_input(input, j, data->input_list) != SUCCESS)
		split_memory_failed(data);
	*i += j - 1;
	return (SUCCESS);
}