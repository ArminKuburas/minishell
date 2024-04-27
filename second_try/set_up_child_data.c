/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/27 02:13:45 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("Inside create command arguments.\n");
	while (temp && temp->type != PIPE)
	{
		if (temp->type == COMMAND_ARGUMENT)
			i++;
		temp = temp->next;
	}
	printf("After while loop. i = %d\n", i);
	if (i == 0)
		return (0);
	child->command_inputs = ft_calloc(i + 1, sizeof(char *));
	if (child->command_inputs == NULL)
		return (1);
	i = 0;
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
	return (0);
}

void	setup_command_inputs(t_shelldata *data, int i)
{
	int				j;
	int				error;
	t_input_list	*temp;

	j = 0;
	temp = data->input_list;
	printf("inside setup command inputs\n");
	while (j < i)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		j++;
	}
	printf("After initial while loop inside setup command inputs j = %d\n", j);
	while (temp->type != COMMAND)
	{
		temp = temp->next;
	}
	printf("after second while loop. temp input equals %s\n", temp->input);
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
			set_all_error(data);
		data->child_data[i].env = data->env_variables;
		i++;
	}
	return (SUCCESS);
}

int	set_up_child_data(t_shelldata *data)
{
	int	processes;

	printf("set_up_child_data\n");
	processes = count_processes(data->input_list);
	printf("processes = %d\n", processes);
	data->command_amount = processes;
	data->child_data
		= (t_child_data *)ft_calloc(processes, sizeof(t_child_data));
	if (data->child_data == NULL)
	{
		ft_putstr_fd("memory allocation failed\n", 2);
		return (NO_MEMORY);
	}
	create_child_data(data, processes);
	return (SUCCESS);
}
