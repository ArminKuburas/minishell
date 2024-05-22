/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:35:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/21 14:23:13 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_commands.c
 * @brief Functions for setting up commands.
 * @details This file contains functions for setting up commands.
*/

/**
 * @brief Checks if the command is a builtin.
 * @param builtin The builtin to be checked.
 * @param command The command to be checked.
 * @return Returns 0 if the command is a builtin, otherwise -1.
*/
static int	check_command(const char *builtin, char *command)
{
	if (ft_strlen(builtin) != ft_strlen(command))
		return (-1);
	if (ft_strcmp((char *)builtin, command) == 0)
		return (0);
	return (-1);
}

/**
 * @brief Checks if the command is a builtin.
 * @param command The command to be checked.
 * @param data The data to be used.
 * @param index The index of the child data.
 * @return Returns SUCCESS if the command is a builtin, otherwise NOT_FOUND.
*/
static int	is_it_builtin(char *command, t_shelldata *data, int index)
{
	const char	builtins[7][20] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit"
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (check_command(builtins[i], command) == 0)
		{
			data->child_data[index].command = ft_strdup(command);
			if (data->child_data[index].command == NULL)
				child_failed(data, NO_MEMORY);
			return (SUCCESS);
		}
		i++;
	}
	return (NOT_FOUND);
}

/**
 * @brief sets up the command.
 * @param command The command to be checked.
 * @param data The data to be used.
 * @param index The index of the child data.
 * @return Returns SUCCESS if the command exists, otherwise NOT_FOUND.
*/
int	setup_command(t_shelldata *data, int index)
{
	t_input_list	*temp;
	int				i;
	int				error;

	temp = data->input_list;
	i = index;
	while (i > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		i--;
	}
	while (temp && temp->type != PIPE)
	{
		if (temp->type == COMMAND)
		{
			printf("command: %s\n", temp->input);
			error = is_it_builtin(temp->input, data, index);
			if (error == NOT_FOUND)
				error = is_it_command(temp->input, data, index);
			return (error);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
