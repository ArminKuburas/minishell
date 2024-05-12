/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/12 15:36:10 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/


int	ft_env(t_shelldata *data)
{
	t_env_list		*temp;
	char			*qm;
	char			*eq;

	qm = "?";
	eq = "=";
	temp = data->env_list;
	if (!temp)
		return (FAILURE);
	while (temp)
	{
		if (ft_strchr(temp->env_var, '=') && temp->env_var_name[0] != '?')
			ft_printf("%s \n", temp->env_var);
		temp = temp->next;
	}
	return (SUCCESS);
}
