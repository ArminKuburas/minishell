/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_assigner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:59:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/22 15:41:31 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file type_assigner.c
 * @brief Functions for assigning types to the input list.
*/

/**
 * @brief Assigns the type of the input list.
 * @param temp The input list to be used.
 * @param command_flag The flag for the command.
 * @return void
*/
static void	assign_command_or_pipe(t_input_list *temp, int *command_flag)
{
	if (temp->type != 0)
		return ;
	if (temp->input[0] == '|')
	{
		temp->type = PIPE;
		*command_flag = 0;
	}
	else
	{
		if (*command_flag == 0)
		{
			temp->type = COMMAND;
			*command_flag = 1;
		}
		else
			temp->type = COMMAND_ARGUMENT;
	}
}

/**
 * @brief Checks if the input is a potential split.
 * @param temp The input list to be used.
 * @return void
*/
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
	}
}

/**
 * @brief Assigns the type of the input list.
 * @param input_list The input list to be used.
 * @return void
*/
void	try_append_or_heredoc(t_input_list *temp)
{
	if (ft_strcmp(temp->input, ">>") == 0)
	{
		temp->type = REDIRECT_APPEND;
		temp->next->type = APPEND_FILE;
		potential_split(temp);
	}
	else if (ft_strcmp(temp->input, "<<") == 0)
	{
		temp->type = REDIRECT_HEREDOC;
		temp->next->type = HEREDOC_FILE;
		potential_split(temp);
	}
}

/**
 * @brief Assigns the type of the input list.
 * @param input_list The input list to be used.
 * @return void
*/
void	input_type_assigner(t_input_list *input_list)
{
	t_input_list	*temp;
	static int		command_flag = 0;

	temp = input_list;
	while (temp != NULL)
	{
		potential_split(temp);
		try_append_or_heredoc(temp);
		if (temp->type == 0 && ft_strcmp(temp->input, ">") == 0)
		{
			temp->type = REDIRECT_OUTPUT;
			temp->next->type = OUTPUT_FILE;
			potential_split(temp);
		}
		else if (temp->type == 0 && ft_strcmp(temp->input, "<") == 0)
		{
			temp->type = REDIRECT_INPUT;
			temp->next->type = INPUT_FILE;
			potential_split(temp);
		}
		else
			assign_command_or_pipe(temp, &command_flag);
		temp = temp->next;
	}
	command_flag = 0;
}
