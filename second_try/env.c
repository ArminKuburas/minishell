/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/24 18:43:06 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
void	my_env(t_shelldata data)
{
	t_env_list	*current_node;

	current_node = data.env_list;
	//if (temp->next)
	//	return ;
	if (!data.env_list)
		return ;
	while (current_node)
	{
		if (ft_strchr(current_node->env_var, '='))
			ft_printf("%s=%s\n", current_node->env_var);
		current_node = data.env_list->next;
	}
}
