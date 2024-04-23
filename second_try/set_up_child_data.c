/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_child_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:42 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/23 22:13:23 by akuburas         ###   ########.fr       */
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

int	check_command(const char *builtin, char *command)
{
	if (ft_strlen(builtin) != ft_strlen(command))
		return (0);
	if (ft_strcmp(builtin, command) == 0)
		return (1);
	return (0);
}

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

int	create_variables(char ***path_variables, t_env_list *env_list)
{
	t_env_list	*temp;
	int			i;

	temp = env_list;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_var_name, "PATH", 4) == 0)
		{
			*path_variables = ft_split(temp->env_var_value, ':');
			if (*path_variables == NULL)
				return (NO_MEMORY);
			return (SUCCESS);
		}
		temp = temp->next;
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
			error = is_it_builtin(temp->input, &data->child_data[index]);
			if (error == NOT_FOUND)
				error = is_it_command(temp->input, data, index);
			return (error);
		}
		temp = temp->next;
	}
	return (SUCCESS);
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
