/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirect_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:51 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 16:27:05 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_redirect_helpers.c
 * @brief Helper functions for setting up redirections.
*/

/**
 * @brief handles ambigious redirect
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
*/
void	ambiguous_redirect(t_shelldata *data, int i, t_input_list *input)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input->old_input, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	data->child_data[i].exit_value = 1;
}

/**
 * @brief handles output error
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
*/
void	handle_output_error(t_shelldata *data, int i, t_input_list *input)
{
	data->child_data[i].fd_out = open(input->input, O_DIRECTORY, 0644);
	if (data->child_data[i].fd_out != -1)
	{
		close(data->child_data[i].fd_out);
		data->child_data[i].fd_out = 0;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	data->child_data[i].exit_value = 1;
}
