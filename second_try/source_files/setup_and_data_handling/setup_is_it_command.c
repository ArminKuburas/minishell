/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_is_it_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:54:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 14:03:24 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	if (*error != FOUND)
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
		if (error == NO_MEMORY)
			return (error);
		if (error == FOUND)
		{
			data->child_data[index].command = temp2;
			if (temp2 != NULL)
				return (SUCCESS);
		}
		i++;
	}
	return (NOT_FOUND);
}

int	check_if_directory(char *input, t_shelldata *data, int index)
{
	int	temp_fd;

	temp_fd = open(input, O_DIRECTORY);
	if (temp_fd != -1)
	{
		close(temp_fd);
		data->child_data[index].exit_value = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (IS_DIRECTORY);
	}
	return (SUCCESS);
}

int	check_if_given_path(char *input, t_shelldata *data, int index)
{
	if (ft_strchr("./", input[0]) != NULL)
	{
		if (access(input, F_OK) == 0)
		{
			if (access(input, X_OK) == 0)
			{
				data->child_data[index].command = ft_strdup(input);
				if (data->child_data[index].command == NULL)
					return (NO_MEMORY);
				return (check_if_directory(input, data, index));
			}
			else
				return (EXECUTION_FORBIDDEN);
		}
		else
			return (NOT_FOUND);
	}
	return (NOT_FOUND);
}

int	is_it_command(char *input, t_shelldata *data, int index)
{
	char	**path_variables;
	int		error;

	path_variables = NULL;
	error = check_if_given_path(input, data, index);
	if (error == SUCCESS)
		return (SUCCESS);
	else if (error != NOT_FOUND)
		return (error);
	if (create_variables(&path_variables, data->env_list) == NO_MEMORY)
		return (NO_MEMORY);
	if (path_variables == NULL)
		return (NOT_FOUND);
	error = find_path(path_variables, data, index, input);
	ft_free_substrings(&path_variables);
	return (error);
}
