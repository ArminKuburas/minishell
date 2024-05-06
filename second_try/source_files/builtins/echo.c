/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:55:23 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 14:17:23 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	free_to_print(t_input_list *temp)
{
	while (temp)
	{
		ft_putstr(temp->input);
		if (temp->next)
			ft_putstr(" ");
		temp = temp->next;
	}
	ft_putstr("\n");
}

void	my_echo(t_input_list *temp)
{
	if (!temp->next)
	{
		ft_putstr("\n");
		return ;
	}
	temp = temp->next;
	if (ft_strncmp(temp->input, "-n", 3) == 0)
	{
		while (ft_strncmp(temp->input, "-n", 3) == 0)
		{
			if (!temp->next)
				return ;
			temp = temp->next;
		}
		while (temp)
		{
			ft_putstr(temp->input);
			if (temp->next)
				ft_putstr(" ");
			temp = temp->next;
		}
	}
	else
		free_to_print(temp);
}
