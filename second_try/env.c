/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/29 17:22:37 by tvalimak         ###   ########.fr       */
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
