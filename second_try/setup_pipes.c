/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:14:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/02 11:22:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_input_pipe(t_shelldata *data, int i)
{
	data->child_data[i].p_fd_in[0] = data->child_data[i - 1].p_fd_out[0];
	data->child_data[i].p_fd_in[1] = data->child_data[i - 1].p_fd_out[1];
	return (SUCCESS);
}

int	setup_output_pipe(t_shelldata *data, int i)
{
	if (pipe(data->child_data[i].p_fd_out) == -1)
		return (NO_PIPE);
	return (SUCCESS);
}

int	setup_pipes(t_shelldata *data, int amount)
{
	t_input_list	*temp;
	int				i;
	int				error;

	temp = data->input_list;
	i = amount;
	error = SUCCESS;
	while (i > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		i--;
	}
	if (temp->type == PIPE)
		error = setup_input_pipe(data, amount);
	temp = temp->next;
	while (temp && temp->type != PIPE)
		temp = temp->next;
	if (error == SUCCESS && temp && temp->type == PIPE)
		error = setup_output_pipe(data, amount);
	return (error);
}
