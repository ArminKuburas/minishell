/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:57 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/19 16:46:41 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* my_env goes through the env list and prints out the variables
   if they are proper key/value pairs*/
void	my_env(t_shelldata data, t_input_list *temp)
{
	if (temp->next)
		return ;
	if (!data.env_list)
		return ;
	while (data.env_list)
	{
		if (ft_strchr(data.env_list->env_var, '='))
			ft_printf("%s=%s\n", data.env_list->env_var);
		data.env_list = data.env_list->next;
	}
}
