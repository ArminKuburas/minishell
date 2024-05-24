/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/20 16:59:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_env.c
 * @brief Built-in env function.
 */

/**
 * @brief Loops through the env variables and prints them.
 * @param temp The environment list.
 * @param fd The file descriptor.
*/
static void	env_loop(t_env_list *temp, int fd)
{
	while (temp)
	{
		if (temp->env_var_value != NULL && temp->env_var_name[0] != '?')
		{
			if (ft_strchr(temp->env_var, '=') == NULL)
			{
				ft_putstr_fd(temp->env_var, fd);
				ft_putendl_fd("=", fd);
			}
			else
				ft_putendl_fd(temp->env_var, fd);
		}
		temp = temp->next;
	}
}

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
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(qm, STDERR_FILENO);
		ft_putstr_fd(" not found\n", STDERR_FILENO);
		return (FAILURE);
	}
	env_loop(temp, fd);
	return (SUCCESS);
}
