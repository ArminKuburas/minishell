/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_cleaning_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:59:04 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 10:59:13 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	if (exit_value == FAILURE)
		exit(1);
}