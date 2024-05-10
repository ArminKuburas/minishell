/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:41:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 14:19:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	dup_special_character(char *input, t_shelldata *data, int *i)
{
	if (ft_strchr("><", input[1]) != NULL && input[0] == input[1])
	{
		if (input[2] != '\0' && ft_strchr("><|", input[2]) != NULL)
		{
			ft_putstr_fd("Error: Syntax error2\n", 2);
			return (FAILURE);
		}
		if (create_input(input, 2, data->input_list) != SUCCESS)
			split_memory_failed(data);
	}
	else
	{
		if (ft_strchr("><|", input[1]) != NULL)
		{
			ft_putstr_fd("Error: Syntax error3\n", 2);
			return (FAILURE);
		}
		if (create_input(input, 1, data->input_list) != SUCCESS)
			split_memory_failed(data);
	}
	*i += strlen_last_input(data->input_list) - 1;
	return (SUCCESS);
}

static int	mini_split_loop(t_shelldata *data)
{
	int		i;

	i = 0;
	while (data->input[i])
	{
		while (data->input[i] == ' ' || data->input[i] == '\t')
			i++;
		if (data->input[i] == '\0')
			break ;
		if (ft_strchr("><|", data->input[i]) != NULL)
		{
			if (dup_special_character(&data->input[i], data, &i) != SUCCESS)
				return (clear_input(data->input_list, FAILURE));
		}
		else
			if (duplicate_input(&data->input[i], data, &i) != SUCCESS)
				return (clear_input(data->input_list, FAILURE));
		if (data->input[i] != '\0')
			i++;
	}
	return (SUCCESS);
}

int	new_mini_split(t_shelldata *data)
{
	data->input_list = ft_calloc(1, sizeof(t_input_list));
	if (data->input_list == NULL)
		return (NO_MEMORY);
	return (mini_split_loop(data));
}
