/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 10:04:42 by akuburas         ###   ########.fr       */
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
}

int	create_child_data(t_shelldata *data, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		setup_redirects(data, i);
		if (data->child_data[i].exit_value == 0)
			if (setup_command(data, i) != SUCCESS)
				return (FAILURE);
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
