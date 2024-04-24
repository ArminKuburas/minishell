/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:04:17 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 10:04:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
