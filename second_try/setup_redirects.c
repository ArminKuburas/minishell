/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/22 16:48:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirect_input(t_child_data *data, t_input_list *input)
{
	return ;
}

void	setup_redirects(t_shelldata *data, int index)
{
	t_input_list	*temp;

	temp = data->input_list;
	while (index > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		index--;
	}
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT_INPUT)
			handle_redirect_input(&data->child_data[index], temp->next);
		if (temp->type == REDIRECT_OUTPUT)
			handle_redirect_output(&data->child_data[index], temp->next);
		if (temp->type == REDIRECT_APPEND)
			handle_redirect_append(&data->child_data[index], temp->next);
		temp = temp->next;
		if (data->child_data[index].exit_value != 0)
			return ;
	}
}
