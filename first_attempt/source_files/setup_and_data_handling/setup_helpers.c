/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:17 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/22 16:58:54 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_helpers.c
 * @brief Helper functions for the setup.
*/

/**
 * @brief Frees child data and closes fds.
 * @param data The child data to be freed and closed.
 * @return void
*/
void	free_child_data(t_child_data *data)
{
	if (data->fd_in != 0 && data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != 0 && data->fd_out != -1)
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

/**
 * @brief Prints error message for command.
 * @param error The error code.
 * @param temp The current input list node.
 * @param child The child data to be used.
 * @return void
*/
static void	print_helper(int error, t_input_list *temp, t_child_data *child)
{
	if (error == NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": command not found\n", 2);
		child->exit_value = 127;
	}
	else if (error == EXECUTION_FORBIDDEN)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		child->exit_value = 126;
	}
	else if (error == NO_PATH)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(temp->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		child->exit_value = 127;
	}
}

/**
 * @brief Prints error message for command.
 * @param error The error code.
 * @param data The data to be used.
 * @param amount The amount of processes.
 * @return void
*/
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
	else if (error != SUCCESS)
		print_helper(error, temp, &data->child_data[amount]);
}

/**
 * @brief helper for create command arguments
 * @param child The child data to be used.
 * @param start The start of the input list.
 * @return void
*/
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

/**
 * @brief Creates the command arguments.
 * @param child The child data to be used.
 * @param start The start of the input list.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
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
		return (NO_MEMORY);
	child->command_inputs[0] = child->command;
	if (i == 0)
		return (SUCCESS);
	cca_helper(child, start);
	return (SUCCESS);
}
