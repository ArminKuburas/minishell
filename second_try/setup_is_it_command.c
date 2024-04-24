/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_is_it_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:54:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 10:03:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_builtin(char *command, t_child_data *child_data)
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

	while (i < 7)
	{
		if (check_command(builtins[i], command) == 1)
		{
			child_data->command = ft_strdup(command);
			if (child_data->command == NULL)
				return (NO_MEMORY);
			return (SUCCESS);
		}
		i++;
	}
	return (NOT_FOUND);
}

void	try_access(char *path, int *error)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			*error = FOUND;
		else
			*error = EXECUTION_FORBIDDEN;
	}
}

char	*create_path(char *path_variable, char *input, int *error)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(path_variable, "/");
	if (temp == NULL)
	{
		*error = NO_MEMORY;
		return (NULL);
	}
	temp2 = ft_strjoin(temp, input);
	free(temp);
	if (temp2 == NULL)
	{
		*error = NO_MEMORY;
		return (NULL);
	}
	try_access(temp2, error);
	if (error == EXECUTION_FORBIDDEN)
	{
		free(temp2);
		temp2 = NULL;
	}
	return (temp2);
}

int	find_path(char **path_variables, t_shelldata *data, int index, char *input)
{
	int		i;
	char	*temp2;
	int		error;

	i = 0;
	error = 0;
	while (path_variables[i] != NULL)
	{
		temp2 = create_path(path_variables[i], input, &error);
		if (error == 0)
			return (error);
		data->child_data[index].command = temp2;
		if (temp2 != NULL)
			return (SUCCESS);
		i++;
	}
	return (NOT_FOUND);
}

int	is_it_command(char *input, t_shelldata *data, int index)
{
	char	**path_variables;
	int		error;

	path_variables = NULL;
	if (create_variables(&path_variables, data->env_list) == NO_MEMORY)
		return (NO_MEMORY);
	if (path_variables == NULL)
		return (NOT_FOUND);
	error = find_path(path_variables, data, index, input);
	return (error);
}
