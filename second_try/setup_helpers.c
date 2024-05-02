/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:17 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/30 11:34:03 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_data(t_child_data *data)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	if (data->fd_out != 0)
		close(data->fd_out);
	if (data->command != NULL)
		free(data->command);
	if (data->command_inputs != NULL)
		free(data->command_inputs);
	if (data->p_fd_out[0] != 0)
		close(data->p_fd_out[0]);
	if (data->p_fd_out[1] != 0)
		close(data->p_fd_out[1]);
}
