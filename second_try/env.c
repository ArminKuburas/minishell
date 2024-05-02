/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/02 11:34:09 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
void	my_env(t_shelldata *data)
{
	t_env_list	*current_node;
	t_env_list	*head;

	head = data->env_list;
	current_node = data->env_list;
	if (!data->env_list)
		return ;
	while (current_node)
		current_node = current_node->next;
	data->env_list = head;
}
