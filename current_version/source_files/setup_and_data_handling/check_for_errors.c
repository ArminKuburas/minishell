/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:25 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/20 19:41:44 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file check_for_errors.c
 * @brief Functions for checking for errors.
 * @details This file contains functions for checking for errors.
*/

/**
 * @brief Checks for syntax errors in the pipe input.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
int	check_pipes(t_shelldata *data)
{
	t_input_list	*temp;

	temp = data->input_list;
	while (temp != NULL)
	{
		if (temp->input[0] == '|')
		{
			if (temp->prev == NULL || temp->prev->input[0] == '|'
				|| temp->next == NULL || temp->next->input[0] == '|')
			{
				ft_putstr_fd("minishell: syntax error", 2);
				ft_putendl_fd(" near unexpected token `|'", 2);
				data->exit_value = 2;
				clear_input(data->input_list, FAILURE);
				return (FAILURE);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
