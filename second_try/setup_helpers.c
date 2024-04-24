/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:17 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 16:28:41 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(t_child_data *data)
{
	if (data->p_fd_in[0] != 0)
		close(data->p_fd_in[0]);
	if (data->p_fd_in[1] != 0)
		close(data->p_fd_in[1]);
	if (data->p_fd_out[0] != 0)
		close(data->p_fd_out[0]);
	if (data->p_fd_out[1] != 0)
		close(data->p_fd_out[1]);
}

void	free_child_data(t_child_data *data, int index)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	if (data->fd_out != 1)
		close(data->fd_out);
	if (data->command != NULL)
		free(data->command);
	if (data->command_inputs != NULL)
		free(data->command_inputs);
	if (index % 2 == 1)
		close_pipes(data);
}
