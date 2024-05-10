/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:17 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 13:52:44 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_child_data(t_child_data *data)
{
	if (data->fd_in != 0)
		close(data->fd_in);
	if (data->fd_out != 0)
		close(data->fd_out);
	if (data->command != NULL)
		free(data->command);
	if (data->command_inputs != NULL)
		free(data->command_inputs);
	if (data->p_fd_out[0] != 0)
		close(data->p_fd_out[0]);
	if (data->p_fd_out[1] != 0)
		close(data->p_fd_out[1]);
}

static void	print_helper(int error, t_input_list *temp, t_child_data *child)
{
	if (error == NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		child->exit_value = 127;
	}
	else if (error == EXECUTION_FORBIDDEN)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		child->exit_value = 126;
	}
}

void	command_error_message(int error, t_shelldata *data, int amount)
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
	else if (error == NOT_FOUND || error == EXECUTION_FORBIDDEN)
		print_helper(error, temp, &data->child_data[amount]);
}

static void	cca_helper(t_child_data *child, t_input_list *start)
{
	t_input_list	*temp;
	int				i;

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
	cca_helper(child, start);
	return (SUCCESS);
}
