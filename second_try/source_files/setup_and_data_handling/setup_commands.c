/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:35:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 14:19:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_command(const char *builtin, char *command)
{
	if (ft_strlen(builtin) != ft_strlen(command))
		return (-1);
	if (ft_strcmp((char *)builtin, command) == 0)
		return (0);
	return (-1);
}

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

/*This function first tries to see if a command exists
If one does exist it tries to check if its perhaps a builtin
If it isn't we will then try to find it. First we try as is
Since it might have the path already there. Otherwise we try
To use the PATH env variable. We handle errors as needed.*/
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
			error = is_it_builtin(temp->input, data, index);
			if (error == NOT_FOUND)
				error = is_it_command(temp->input, data, index);
			return (error);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
