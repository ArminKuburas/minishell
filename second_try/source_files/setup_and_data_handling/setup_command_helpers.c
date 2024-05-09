/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_command_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:48:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 13:49:03 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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