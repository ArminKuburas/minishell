/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:48:31 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/19 17:03:15 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(t_shelldata data, t_input_list *temp)
{
	if (temp->next)
		return ;
	ft_printf("exit\n");
	exit(0);
}