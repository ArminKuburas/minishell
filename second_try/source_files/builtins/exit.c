/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:48:31 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 14:17:56 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	my_exit(t_shelldata *data, t_input_list *temp)
{
	(void)data;
	if (temp->next)
		return ;
	ft_printf("exit\n");
	exit(0);
}
