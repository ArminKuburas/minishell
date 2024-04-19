/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assigner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:59:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/19 06:26:26 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_command_or_pipe(t_input_list *temp)
{
	static int	command_flag = 0;

	if (temp->type != 0)
		return ;
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
	if (temp->next == NULL)
		command_flag = 0;
}

void	potential_split(t_input_list *temp)
{
	int	i;

	i = 1;
	if (temp->input[0] == '$')
	{
		while (temp->input[i] != '\0')
		{
			if (temp->input[i] == '$' && temp->input[i + 1] == '\0')
				return ;
			i++;
		}
		temp->word_split = POTENTIAL_SPLIT;
		printf("This is a potential split: %s\n", temp->input);
	}
}

void	try_append_or_heredoc(t_input_list *temp)
{
	if (ft_strcmp(temp->input, ">>") == 0)
	{
		temp->type = REDIRECT_APPEND;
		temp = temp->next;
		temp->type = APPEND_FILE;
		potential_split(temp);
	}
	else if (ft_strcmp(temp->input, "<<") == 0)
	{
		temp->type = REDIRECT_HEREDOC;
		temp = temp->next;
		temp->type = HEREDOC_FILE;
		potential_split(temp);
	}
}

void	input_type_assigner(t_input_list *input_list)
{
	t_input_list	*temp;

	temp = input_list;
	while (temp != NULL)
	{
		potential_split(temp);
		try_append_or_heredoc(temp);
		if (ft_strcmp(temp->input, ">") == 0)
		{
			temp->type = REDIRECT_OUTPUT;
			temp = temp->next;
			temp->type = OUTPUT_FILE;
			potential_split(temp);
		}
		else if (ft_strcmp(temp->input, "<") == 0)
		{
			temp->type = REDIRECT_INPUT;
			temp = temp->next;
			temp->type = INPUT_FILE;
			potential_split(temp);
		}
		else
			assign_command_or_pipe(temp);
		temp = temp->next;
	}
}
