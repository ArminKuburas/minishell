/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/15 12:14:21 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_env.c
 * @brief Built-in env function.
 */

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/

/**
 * @brief Prints the env variables.
 * @param data The struct containing shell data.
 * @return Returns 0 if successful, 1 if not.
 */
int	ft_env(t_shelldata *data, int fd)
{
	t_env_list		*temp;
	char			*qm;

	qm = "?";
	temp = data->env_list;
	if (!temp)
	{
		ft_putstr_fd("bananashell: env: ", STDERR_FILENO);
		ft_putstr_fd(qm, STDERR_FILENO);
		ft_putstr_fd(" not found\n", STDERR_FILENO);
		return (FAILURE);
	}
	while (temp)
	{
		if (temp->env_var_value != NULL && temp->env_var_name[0] != '?')
		{
			if (ft_strchr(temp->env_var, '=') != NULL)
				ft_putendl_fd(temp->env_var, fd);
			else
				ft_putendl_fd(temp->env_var, fd);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
