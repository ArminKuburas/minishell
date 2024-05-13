/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 06:50:18 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file set_up_child_data.c
 * @brief Functions for setting up child data.
*/

/**
 * @brief Counts the amount of processes in the input list.
 * @param start The start of the input list.
 * @return Returns the amount of processes.
*/

int	count_processes(t_input_list *start)
{
	t_input_list	*temp;
	int				amount;

	temp = start;
	amount = 1;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
			amount++;
		temp = temp->next;
	}
	return (amount);
}

/**
 * @brief Sets up the command inputs
 * @param data The data to be used.
 * @param i The index of the child data.
 * @return void
*/

void	setup_command_inputs(t_shelldata *data, int i)
{
	int				j;
	int				error;
	t_input_list	*temp;

	j = 0;
	temp = data->input_list;
	while (j < i)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		j++;
	}
	while (temp != NULL && temp->type != COMMAND)
	{
		temp = temp->next;
	}
	error = create_command_arguments(&data->child_data[i], temp);
	data->child_data[i].exit_value = error;
}

/**
 * @brief creates the child data
 * @param data The data to be used.
 * @param amount The amount of processes.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/

int	create_child_data(t_shelldata *data, int amount)
{
	int	i;
	int	error;

	i = 0;
	while (i < amount)
	{
		setup_redirects(data, i);
		if (data->child_data[i].exit_value == 0)
		{
			error = setup_command(data, i);
			if (error != SUCCESS)
				command_error_message(error, data, i);
			else
				setup_command_inputs(data, i);
		}
		error = setup_pipes(data, i);
		if (error != SUCCESS)
			child_failed(data, NO_PIPE);
		data->child_data[i].env = data->env_variables;
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Sets up the child data.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/

int	set_up_child_data(t_shelldata *data)
{
	int	processes;
	// technically still not done with handling exit cases here. go into create child data and validate things one by one
	processes = count_processes(data->input_list);
	data->command_amount = processes;
	data->child_data
		= (t_child_data *)ft_calloc(processes, sizeof(t_child_data));
	if (data->child_data == NULL)
		split_memory_failed(data);
	create_child_data(data, processes);
	return (SUCCESS);
}
