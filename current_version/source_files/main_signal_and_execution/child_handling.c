/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:52:53 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/26 02:49:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file child_handling.c
 * @brief Functions for handling child processes.
 * @details This file contains functions for handling child processes.
*/

/**
 * @brief Handles the case where fork fails.
 * @param data The data to be used.
 * @return void
*/
void	fork_failed(t_shelldata *data, int amount)
{
	int	i;

	i = 0;
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
		i++;
	}
	clear_input(data->input_list, FAILURE);
	clear_env_list(data->env_list, FAILURE);
	free(data->env_variables);
	free(data->input);
	free(data->pwd);
	free(data->old_pwd);
	rl_clear_history();
	i = 0;
	while (i < amount)
	{
		waitpid(data->child_data[i].pid, &data->child_data[i].exit_value, 0);
		i++;
	}
	free(data->child_data);
	exit(1);
}

/**
 * @brief Executes the commands in the child processes.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
int	execute_commands(t_shelldata *data)
{
	int				i;

	i = 0;
	child_signals();
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
	standby_signals();
	wait_for_children(data);
	free(data->child_data);
	return (SUCCESS);
}

/**
 * @brief Handles the case where there is only one builtin command.
 * @param data The data to be used.
 * @return Returns the exit value of the builtin command.
*/
int	one_builtin(t_shelldata *data)
{
	data->exit_value = use_builtin(&data->child_data[0],
			data->child_data[0].fd_out, data);
	free_child_data(&data->child_data[0]);
	free(data->child_data);
	data->child_data = NULL;
	if (data->exit_value == NO_MEMORY)
		clean_everything_up(data, FAILURE);
	return (data->exit_value);
}

/**
 * @brief Pre-checks before executing the child processes.
 * @param data The data to be used.
 * @return Returns the exit value of the child processes.
*/
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

/**
 * @brief Handles the child processes.
 * @param data The data to be used.
 * @return void
*/
void	child_handling(t_shelldata *data)
{
	child_pre_check(data);
	if (create_exit_value_env(data) != SUCCESS)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd("memory allocation failed", STDERR_FILENO);
		clear_input(data->input_list, FAILURE);
		clear_env_list(data->env_list, FAILURE);
		free(data->env_variables);
		free(data->input);
		rl_clear_history();
		exit(1);
	}
}
