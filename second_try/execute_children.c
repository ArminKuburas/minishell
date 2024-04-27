/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 02:36:27 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/28 02:05:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_child_pipes(t_child_data *child_data)
{
	if (child_data->p_fd_out[1] != 0)
	{
		if (dup2(child_data->p_fd_out[1], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed1\n", 2);
			return (NO_DUP);
		}
	}
	if (child_data->p_fd_in[0] != 0)
	{
		if (dup2(child_data->p_fd_in[0], STDIN_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed2\n", 2);
			return (NO_DUP);
		}
	}
	return (SUCCESS);
}

int	check_fds(t_child_data *child_data)
{
	if (child_data->fd_in != 0)
	{
		if (dup2(child_data->fd_in, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed3\n", 2);
			return (NO_DUP);
		}
	}
	if (child_data->fd_out != 0)
	{
		if (dup2(child_data->fd_out, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed4\n", 2);
			return (NO_DUP);
		}
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
	clear_input(data->input_list, SUCCESS);
	exit(exit_value);
}

void	child_handler(t_shelldata *data, t_child_data *child_data, int i)
{
	if (check_child_pipes(child_data) != SUCCESS)
		clean_everything_up(data, FAILURE);
	if (check_fds(child_data) != SUCCESS)
		clean_everything_up(data, FAILURE);
	close_my_fds(child_data);
	clean_other_children(data, i);
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
		ft_putstr_fd("minishell: fork failed\n", 2);
		data->exit_value = 1;
		return (FAILURE);
	}
	if (child_data->pid == 0)
	{
		child_handler(data, child_data, i);
	}
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
		if (data->child_data[i].command != NULL
			&& data->child_data[i].exit_value == 0)
			waitpid(data->child_data[i].pid,
				&data->child_data[i].exit_value, 0);
		i++;
	}
	return (SUCCESS);
}
