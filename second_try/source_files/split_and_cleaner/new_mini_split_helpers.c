/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini_split_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 04:14:46 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 20:34:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file new_mini_split_helpers.c
 * @brief Helper functions for the mini_split function.
*/


/**
 * @brief Finds the closing quote.
 * @param quote The quote to be found.
 * @param c The character to be checked.
 * @return void
*/
static void	quote_found(char *quote, char c)
{
	if (*quote == '\0')
		*quote = c;
	else if (*quote == c)
		*quote = '\0';
}

/**
 * @brief Splits the memory if the allocation fails.
 * @param data The data to be used.
 * @return void
*/
void	split_memory_failed(t_shelldata *data)
{
	ft_putstr_fd("bananashell: Memory allocation failed\n", 2);
	clear_input(data->input_list, FAILURE);
	free(data->input);
	clear_env_list(data->env_list, FAILURE);
	rl_clear_history();
	exit(1);
}

/**
 * @brief Creates a new input node.
 * @param input The input to be used.
 * @param j The index to be used.
 * @param input_list The input list to be used.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
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
