/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute_help_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:10:45 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/20 19:51:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file child_execute_help_functions.c
 * @brief Helper functions for child execution.
*/

/**
 * @brief Checks the exit value of the child process.
 * @param child_data The child data to be used.
 * @param already_printed If the exit value has already been printed.
 * @return void
*/
void	check_exit_value(t_child_data *child_data, int already_printed)
{
	if (child_data->exit_value == 2 && already_printed == NO)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		already_printed = YES;
		child_data->exit_value = 130;
	}
	else if (child_data->exit_value == 3 && already_printed == NO)
	{
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		already_printed = YES;
		child_data->exit_value = 131;
	}
	else if ((WIFEXITED(child_data->exit_value)
			&& child_data->exit_value == NO_EXECVE))
	{
		child_data->exit_value = 1;
		ft_putstr_fd("minishell: exec failed: ", STDERR_FILENO);
		ft_putendl_fd(child_data->command, STDERR_FILENO);
	}
	else if (WIFEXITED(child_data->exit_value)
		&& child_data->exit_value == NO_COMMAND)
	{
		child_data->exit_value = 1;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(child_data->command, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (child_data->exit_value > 255)
		child_data->exit_value = child_data->exit_value / 256;
}

/**
 * @brief Waits for all children to finish.
 * @param data The data to be used.
 * @return void
*/
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
		check_exit_value(&data->child_data[i], already_printed);
		free_child_data(&data->child_data[i]);
		data->exit_value = data->child_data[i].exit_value;
		i++;
	}
}

/**
 * @brief Checks if the command is a builtin command and executes it.
 * @param child_data The child data to be used.
 * @param fd The file descriptor to be used.
 * @param data The data to be used.
 * @return Returns SUCCESS if the command is a builtin command.
*/
int	use_builtin(t_child_data *child_data, int fd, t_shelldata *data)
{
	if (fd == 0)
		fd = STDOUT_FILENO;
	if (ft_strcmp(child_data->command, "echo") == 0)
		return (ft_echo(child_data, fd));
	else if (ft_strcmp(child_data->command, "cd") == 0)
		return (ft_cd(data, child_data->command_inputs));
	else if (ft_strcmp(child_data->command, "pwd") == 0)
		return (ft_pwd(data->pwd, fd));
	else if (ft_strcmp(child_data->command, "export") == 0)
		return (ft_export(data, child_data->command_inputs, fd));
	else if (ft_strcmp(child_data->command, "unset") == 0)
		return (ft_unset(data, child_data->command_inputs));
	else if (ft_strcmp(child_data->command, "env") == 0)
		return (ft_env(data, fd));
	else if (ft_strcmp(child_data->command, "exit") == 0)
		return (ft_exit(data, child_data->command_inputs));
	return (FAILURE);
}

/**
 * @brief Checks if the child has pipes and sets them up.
 * @param child_data The child data to be used.
 * @return Returns SUCCESS if everything went well, otherwise NO_DUP.
*/
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
