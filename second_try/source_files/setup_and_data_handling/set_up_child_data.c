/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 14:19:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	print_command_error_message(int error, t_shelldata *data, int amount)
{
	t_input_list	*temp;
	int				i;

	temp = data->input_list;
	i = amount;
	while (i > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		i--;
	}
	while (temp->type != COMMAND)
		temp = temp->next;
	if (error == NO_MEMORY)
		ft_putstr_fd("memory allocation failed\n", 2);
	else if (error == NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": command not found\n", 2);
		data->child_data[amount].exit_value = 127;
	}
	else if (error == EXECUTION_FORBIDDEN)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->child_data[amount].exit_value = 126;
	}
}

int	create_command_arguments(t_child_data *child, t_input_list *start)
{
	t_input_list	*temp;
	int				i;

	i = 0;
	temp = start;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == COMMAND_ARGUMENT)
			i++;
		temp = temp->next;
	}
	child->command_inputs = ft_calloc(i + 2, sizeof(char *));
	if (child->command_inputs == NULL)
		return (FAILURE);
	child->command_inputs[0] = child->command;
	if (i == 0)
		return (SUCCESS);
	i = 1;
	temp = start;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == COMMAND_ARGUMENT)
		{
			child->command_inputs[i] = temp->input;
			i++;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

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

void	set_all_error(t_shelldata *data)
{
	int	i;

	i = 0;
	while (i < data->command_amount)
	{
		if (data->child_data[i].exit_value == 0)
			data->child_data[i].exit_value = 1;
		i++;
	}
}

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
				print_command_error_message(error, data, i);
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

int	set_up_child_data(t_shelldata *data)
{
	int	processes;

	processes = count_processes(data->input_list);
	data->command_amount = processes;
	data->child_data
		= (t_child_data *)ft_calloc(processes, sizeof(t_child_data));
	if (data->child_data == NULL)
		split_memory_failed(data);
	create_child_data(data, processes);
	return (SUCCESS);
}
