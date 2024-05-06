/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 02:36:27 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 10:41:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	clean_other_children(t_shelldata *data, int i)
{
	int	j;

	j = 0;
	while (j < data->command_amount)
	{
		if (j != i)
		{
			free(data->child_data[j].command);
			data->child_data[j].command = NULL;
			free(data->child_data[j].command_inputs);
			data->child_data[j].command_inputs = NULL;
			close_other_fds(data, j, i);
		}
		j++;
	}
}

void	execve_failed_cleanup(t_shelldata *data, t_child_data *child_data)
{
	free(child_data->command);
	child_data->command = NULL;
	free(child_data->command_inputs);
	child_data->command_inputs = NULL;
	free(data->input);
	data->input = NULL;
	free(data->pwd);
	data->pwd = NULL;
	clear_env_list(data->env_list, SUCCESS);
	free(data->env_variables);
	free(data->child_data);
	ft_putstr_fd("clear input being called inside execve_failed_cleanup\n", 2);
	clear_input(data->input_list, SUCCESS);
}

void	clean_everything_up(t_shelldata *data, int exit_value)
{
	int	i;

	free(data->input);
	data->input = NULL;
	free(data->pwd);
	data->pwd = NULL;
	clear_env_list(data->env_list, SUCCESS);
	free(data->env_variables);
	i = 0;
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
	}
	free(data->child_data);
	ft_putstr_fd("clear input being called inside clean_everything_up\n", 2);
	clear_input(data->input_list, SUCCESS);
	if (exit_value == FAILURE)
		exit(1);
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
	// else if (ft_strcmp(child_data->command, "export") == 0)
	// 	return (ft_export(child_data->command_inputs));
	// else if (ft_strcmp(child_data->command, "unset") == 0)
	// 	return (ft_unset(child_data->command_inputs));
	// else if (ft_strcmp(child_data->command, "env") == 0)
	// 	return (ft_env(child_data->command_inputs, fd));
	// else if (ft_strcmp(child_data->command, "exit") == 0)
	// 	return (ft_exit(child_data->command_inputs));
	return (FAILURE);
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
		exit(errno);
	}
}

int	execute_child(t_shelldata *data, t_child_data *child_data, int i)
{
	child_data->pid = fork();
	if (child_data->pid == -1)
	{
		data->exit_value = 1;
		return (FAILURE);
	}
	if (child_data->pid == 0)
		child_handler(data, child_data, i);
	return (SUCCESS);
}

int	execute_commands(t_shelldata *data)
{
	int				i;

	i = 0;
	while (i < data->command_amount)
	{
		if (data->child_data[i].command != NULL
			&& data->child_data[i].exit_value == 0)
		{
			if (execute_child(data, &data->child_data[i], i) != SUCCESS)
				return (FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
		data->exit_value = data->child_data[i].exit_value;
		if (data->child_data[i].command != NULL
			&& data->child_data[i].exit_value == 0)
			waitpid(data->child_data[i].pid,
				&data->child_data[i].exit_value, 0);
		i++;
	}
	return (SUCCESS);
}

int	one_builtin(t_shelldata *data)
{
	int	return_value;

	return_value = use_builtin(&data->child_data[0],
			data->child_data[0].fd_out, data);
	data->exit_value = return_value;
	free_child_data(&data->child_data[0]);
	return (return_value);
}

int	child_pre_check(t_shelldata *data)
{
	if (data->command_amount == 1)
	{
		if (data->child_data[0].command != NULL
			&& ft_strchr("/.", data->child_data[0].command[0]) == NULL)
			return (one_builtin(data));
		else
			return (execute_commands(data));
	}
	return (execute_commands(data));
}
