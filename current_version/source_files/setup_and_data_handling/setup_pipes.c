/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:14:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/17 12:02:12 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_pipes.c
 * @brief Functions for setting up pipes.
*/

/**
 * @brief Sets up the input pipe.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @return Returns the error code.
*/
static int	setup_input_pipe(t_shelldata *data, int i)
{
	data->child_data[i].p_fd_in[0] = data->child_data[i - 1].p_fd_out[0];
	data->child_data[i].p_fd_in[1] = data->child_data[i - 1].p_fd_out[1];
	return (SUCCESS);
}

/**
 * @brief Sets up the output pipe.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @return Returns the error code.
*/
int	setup_output_pipe(t_shelldata *data, int i)
{
	if (pipe(data->child_data[i].p_fd_out) == -1)
		return (NO_PIPE);
	return (SUCCESS);
}

/**
 * @brief Sets up the pipes.
 * @param data The data to be used.
 * @param amount The amount of pipes.
 * @return Returns the error code.
*/
int	setup_pipes(t_shelldata *data, int amount)
{
	t_input_list	*temp;
	int				i;
	int				error;

	temp = data->input_list;
	i = amount;
	error = SUCCESS;
	while (i > 0 && temp->next != NULL)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		if (temp->next != NULL)
			temp = temp->next;
		i--;
	}
	if (temp->prev && temp->prev->type == PIPE)
		error = setup_input_pipe(data, amount);
	temp = temp->next;
	while (temp && temp->type != PIPE)
		temp = temp->next;
	if (temp)
		error = setup_output_pipe(data, amount);
	return (error);
}
