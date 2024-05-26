/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_command_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/26 13:25:21 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file assign_command_type.c
 * @brief Assigns the command type to the input list.
*/

static void	assign_helper(t_input_list *temp, t_shelldata *data)
{
	temp->type = EMPTY;
	while (temp != NULL)
	{
		if (temp->type == COMMAND_ARGUMENT)
		{
			temp->type = COMMAND;
			assign_command_type(data);
			break ;
		}
		temp = temp->next;
	}
}

/**
 * @brief Assigns the command type to the input list.
 * @details It checks if the initial command is empty.
 * @param data The data to be assigned.
*/
void	assign_command_type(t_shelldata *data)
{
	t_input_list	*temp;

	temp = data->input_list;
	while (temp != NULL)
	{
		if (temp->type == COMMAND)
		{
			if (ft_strlen(temp->input) == 0
				&& (ft_strchr(temp->old_input, '"') == NULL
					&& ft_strchr(temp->old_input, '\'') == NULL))
			{
				assign_helper(temp, data);
			}
			break ;
		}
		temp = temp->next;
	}
}
