/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/27 14:55:24 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
void	my_env(t_shelldata *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	if (!data->env_list)
		return ;
	while (temp)
	{
		if (ft_strchr(temp->env_var, '=') && temp->env_var)
			ft_printf("%s\n", temp->env_var);
		temp = temp->next;
	}
}
