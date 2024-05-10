/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 02:36:27 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/10 15:21:01 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_fds(t_child_data *child_data)
{
	if (child_data->fd_in != 0)
	{
		if (dup2(child_data->fd_in, STDIN_FILENO) == -1)
			return (NO_DUP);
		close(child_data->fd_in);
		child_data->fd_in = 0;
	}
	if (child_data->fd_out != 0)
	{
		if (dup2(child_data->fd_out, STDOUT_FILENO) == -1)
			return (NO_DUP);
		close(child_data->fd_out);
		child_data->fd_out = 0;
	}
	return (SUCCESS);
}

void	close_my_fds(t_child_data *child_data)
{
	if (child_data->fd_in != 0)
		close(child_data->fd_in);
	if (child_data->fd_out != 0)
		close(child_data->fd_out);
	if (child_data->p_fd_out[0] != 0)
		close(child_data->p_fd_out[0]);
	if (child_data->p_fd_out[1] != 0)
		close(child_data->p_fd_out[1]);
	if (child_data->p_fd_in[0] != 0)
		close(child_data->p_fd_in[0]);
	if (child_data->p_fd_in[1] != 0)
		close(child_data->p_fd_in[1]);
}

void	close_other_fds(t_shelldata *data, int j, int i)
{
	if (data->child_data[j].fd_in != 0)
		close(data->child_data[j].fd_in);
	if (data->child_data[j].fd_out != 0)
		close(data->child_data[j].fd_out);
	if (j != i - 1)
	{
		if (data->child_data[j].p_fd_out[0] != 0)
			close(data->child_data[j].p_fd_out[0]);
		if (data->child_data[j].p_fd_out[1] != 0)
			close(data->child_data[j].p_fd_out[1]);
	}
	if (j != i + 1)
	{
		if (data->child_data[j].p_fd_in[0] != 0 && j != i)
			close(data->child_data[j].p_fd_in[0]);
		if (data->child_data[j].p_fd_in[1] != 0 && j != i)
			close(data->child_data[j].p_fd_in[1]);
	}
}

void	child_handler(t_shelldata *data, t_child_data *child_data, int i)
{
	if (check_child_pipes(child_data) != SUCCESS)
		clean_everything_up(data, FAILURE);
	if (check_fds(child_data) != SUCCESS)
		clean_everything_up(data, FAILURE);
	close_my_fds(child_data);
	clean_other_children(data, i);
	if (ft_strchr("/.", child_data->command[0]) == NULL)
	{
		if (use_builtin(child_data, STDOUT_FILENO, data) == SUCCESS)
			exit(0);
		else
		{
			execve_failed_cleanup(data, child_data);
			exit(child_data->exit_value);
		}
	}
	if (execve(child_data->command,
			child_data->command_inputs, child_data->env) == -1)
	{
		execve_failed_cleanup(data, child_data);
		exit(NO_EXECVE);
	}
}

int	execute_child(t_shelldata *data, t_child_data *child_data, int i)
{
	child_data->pid = fork();
	if (child_data->pid == -1)
		fork_failed(data);
	if (child_data->pid == 0)
	{
		child_handler(data, child_data, i);
	}
	return (SUCCESS);
}
