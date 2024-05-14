/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/14 05:27:00 by akuburas         ###   ########.fr       */
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
int	ft_env(t_shelldata *data)
{
	t_env_list		*temp;
	char			*qm;

	qm = "?";
	temp = data->env_list;
	if (!temp)
	{
		ft_printf("bananashell: env: %s not found\n", qm);
		return (FAILURE);
	}
	while (temp)
	{
		if (temp->env_var_value != NULL && temp->env_var_name[0] != '?')
		{
			if (ft_strchr(temp->env_var, '=') != NULL)
				ft_printf("%s \n", temp->env_var);
			else
				ft_printf("%s= \n", temp->env_var);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
