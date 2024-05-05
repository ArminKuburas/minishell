/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:58:25 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/05 21:40:46 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This is a simple function. It finds all the pipes
and checks if there is input before and after the pipe
If not then it prints out a syntax error.
*/
int	check_pipes(t_shelldata *data)
{
	t_input_list	*temp;

	temp = data->input_list;
	while (temp != NULL)
	{
		if (temp->type == PIPE)
		{
			if (temp->prev == NULL || temp->next == NULL)
			{
				ft_putstr_fd("bananashell: syntax error", 2);
				ft_putendl_fd(" near unexpected token `|'", 2);
				data->exit_value = 2;
				printf("clear input being called inside check_pipes\n");
				clear_input(data->input_list, FAILURE);
				return (FAILURE);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}