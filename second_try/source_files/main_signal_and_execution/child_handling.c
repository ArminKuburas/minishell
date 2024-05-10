/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:52:53 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 10:53:17 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	fork_failed(t_shelldata *data)
{
	int	i;

	i = 0;
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
		i++;
	}
	free(data->child_data);
	clear_input(data->input_list, FAILURE);
	clear_env_list(data->env_list, FAILURE);
	free(data->env_variables);
	free(data->input);
	rl_clear_history();
	exit(1);
}

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

int	one_builtin(t_shelldata *data)
{
	data->exit_value = use_builtin(&data->child_data[0],
			data->child_data[0].fd_out, data);
	free_child_data(&data->child_data[0]);
	free(data->child_data);
	return (data->exit_value);
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

void	child_handling(t_shelldata *data)
{
	child_pre_check(data);
	if (create_exit_value_env(data) != SUCCESS)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd("Malloc failed", STDERR_FILENO);
		clear_input(data->input_list, FAILURE);
		clear_env_list(data->env_list, FAILURE);
		free(data->env_variables);
		free(data->input);
		rl_clear_history();
		exit(1);
	}
}
