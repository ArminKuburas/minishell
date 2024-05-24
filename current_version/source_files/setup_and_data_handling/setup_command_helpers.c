/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:48:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 20:29:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_command_helpers.c
 * @brief Helper functions for setting up commands.
 */

/**
 * @brief Creates variables for the path.
 * @param path_variables The path variables.
 * @param env_list The environment list.
 * @return Returns the error code.
 */
int	create_variables(char ***path_variables, t_env_list *env_list)
{
	t_env_list	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->env_var_name, "PATH") == 0)
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

/**
 * @brief Tries to access the path.
 * @param path The path to be accessed.
 * @param error The error code.
 */
void	try_access(char *path, int *error)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			*error = FOUND;
		else
			*error = EXECUTION_FORBIDDEN;
	}
	else
		*error = NOT_FOUND;
}
