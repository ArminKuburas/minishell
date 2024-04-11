/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assigner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:59:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/11 07:39:43 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_command_or_pipe(t_input_list *temp)
{
	static int	command_flag = 0;

	if (temp->input[0] == '|')
	{
		temp->type = PIPE;
		command_flag = 0;
	}
	else
	{
		if (command_flag == 0)
		{
			temp->type = COMMAND;
			command_flag = 1;
		}
		else
			temp->type = COMMAND_ARGUMENT;
	}
}

void	input_type_assigner(t_input_list *input_list)
{
	t_input_list	*temp;

	temp = input_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->input, ">>") == 0)
		{
			temp->type = REDIRECT_APPEND;
			temp = temp->next;
			temp->type = APPEND_FILE;
		}
		else if (ft_strcmp(temp->input, "<<") == 0)
		{
			temp->type = REDIRECT_HEREDOC;
			temp = temp->next;
			temp->type = HEREDOC_FILE;
		}
		else if (temp->input[0] == '>')
		{
			temp->type = REDIRECT_OUTPUT;
			temp = temp->next;
			temp->type = OUTPUT_FILE;
		}
		else if (temp->input[0] == '<')
		{
			temp->type = REDIRECT_INPUT;
			temp = temp->next;
			temp->type = INPUT_FILE;
		}
		else
			assign_command_or_pipe(temp);
		temp = temp->next;
	}
}
