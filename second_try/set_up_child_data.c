/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 23:51:20 by akuburas         ###   ########.fr       */
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

		}
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
	{
		ft_putstr_fd("memory allocation failed\n", 2);
		return (NO_MEMORY);
	}
	create_child_data(data, processes);
	return (SUCCESS);
}
