/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 14:17:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
int	my_env(t_shelldata *data)
{
	t_env_list	*current_node;
	t_env_list	*head;
	char		*qm;
	char		*us;

	qm = "?";
	us = "_";
	head = data->env_list;
	current_node = data->env_list;
	if (!data->env_list)
		return (FAILURE);
	while (current_node)
	{
		if (ft_strcmp(current_node->env_var_name, qm) \
		&& ft_strcmp(current_node->env_var_name, us))
			ft_printf("%s \n", current_node->env_var);
		current_node = current_node->next;
	}
	data->env_list = head;
	return (SUCCESS);
}
