/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/28 13:25:36 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
   /*
void	my_env(t_shelldata *data)
{
	if (!data->env_list)
		return ;
	while (data->env_list)
	{
		if (ft_strchr(data->env_list->env_var, '=') && data->env_list->env_var)
			ft_printf("%s\n", data->env_list->env_var);
		data->env_list = data->env_list->next;
	}
	ft_printf("env succeeded\n");
}*/

void	my_env(t_shelldata *data)
{
	t_env_list	*current_node;
	t_env_list	*head;

	head = data->env_list;
	current_node = data->env_list;
	if (!data->env_list)
		return ;
	while (current_node)
	{
		if (ft_strchr(current_node->env_var, '='))
			ft_printf("%s\n", current_node->env_var);
		current_node = current_node->next;
	}
	data->env_list = head;
}
