/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_help_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:10:45 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 12:18:23 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	wait_for_children(t_shelldata *data)
{
	int	i;
	int	already_printed;

	i = 0;
	already_printed = NO;
	while (i < data->command_amount)
	{
		if (data->child_data[i].command != NULL
			&& data->child_data[i].exit_value == 0)
			waitpid(data->child_data[i].pid,
				&data->child_data[i].exit_value, 0);
		if (data->child_data[i].exit_value == 2 && already_printed == NO)
		{
			ft_putendl_fd("", STDOUT_FILENO);
			already_printed = YES;
		}
		data->exit_value = data->child_data[i].exit_value;
		i++;
	}
}

int	use_builtin(t_child_data *child_data, int fd, t_shelldata *data)
{
	if (fd == 0)
		fd = STDOUT_FILENO;
	if (ft_strcmp(child_data->command, "echo") == 0)
		return (ft_echo(child_data, fd));
	// else if (ft_strcmp(child_data->command, "cd") == 0)
	// 	return (ft_cd(child_data->command_inputs));
	else if (ft_strcmp(child_data->command, "pwd") == 0)
		return (ft_pwd(data->pwd));
	else if (ft_strcmp(child_data->command, "export") == 0)
		return (ft_export(data, child_data->command_inputs, fd));
	else if (ft_strcmp(child_data->command, "unset") == 0)
		return (ft_unset(data, child_data->command_inputs));
	else if (ft_strcmp(child_data->command, "env") == 0)
		return (my_env(data));
	// else if (ft_strcmp(child_data->command, "exit") == 0)
	// 	return (ft_exit(child_data->command_inputs));
	return (FAILURE);
}

int	check_child_pipes(t_child_data *child_data)
{
	if (child_data->p_fd_out[1] != 0)
	{
		if (dup2(child_data->p_fd_out[1], STDOUT_FILENO) == -1)
			return (NO_DUP);
		close(child_data->p_fd_out[1]);
		close(child_data->p_fd_out[0]);
		child_data->p_fd_out[1] = 0;
		child_data->p_fd_out[0] = 0;
	}
	if (child_data->p_fd_in[0] != 0)
	{
		if (dup2(child_data->p_fd_in[0], STDIN_FILENO) == -1)
			return (NO_DUP);
		close(child_data->p_fd_in[0]);
		close(child_data->p_fd_in[1]);
		child_data->p_fd_in[0] = 0;
		child_data->p_fd_in[1] = 0;
	}
	return (SUCCESS);
}