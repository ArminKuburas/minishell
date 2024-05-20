/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:41:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/20 19:22:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file new_mini_split.c
 * @brief Functions for splitting the input.
*/

/**
 * @brief Duplicates the special characters.
 * @param input The input to be used.
 * @param data The data to be used.
 * @param i The index of the input.
 * @return Returns the error code.
*/
static int	dup_special_character(char *input, t_shelldata *data, int *i)
{
	if (ft_strchr("><", input[1]) != NULL && input[0] == input[1])
	{
		if (input[2] != '\0' && ft_strchr("><|", input[2]) != NULL)
		{
			ft_putstr_fd("minishell: error near unexpected token\n", 2);
			data->exit_value = 1;
			return (FAILURE);
		}
		if (create_input(input, 2, data->input_list) != SUCCESS)
			split_memory_failed(data);
	}
	else
	{
		if (ft_strchr("><|", input[1]) != NULL)
		{
			ft_putstr_fd("Error: error near unexpected token\n", STDERR_FILENO);
			data->exit_value = 1;
			return (FAILURE);
		}
		if (create_input(input, 1, data->input_list) != SUCCESS)
			split_memory_failed(data);
	}
	*i += strlen_last_input(data->input_list) - 1;
	return (SUCCESS);
}

/**
 * @brief the mini split loop. It splits the original input
 * @param data The data to be used.
 * @return Returns the error code.
*/
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

/**
 * @brief The new mini split function. It splits the input.
 * @param data The data to be used.
 * @return Returns the error code.
*/
int	new_mini_split(t_shelldata *data)
{
	data->input_list = ft_calloc(1, sizeof(t_input_list));
	if (data->input_list == NULL)
		return (NO_MEMORY);
	return (mini_split_loop(data));
}
