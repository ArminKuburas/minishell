/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_printers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:28:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/26 02:34:09 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief Prints a syntax error message.
 * @param input The input to be used.
 * @return void
*/
void	print_syntax_error(t_input_list *input)
{
	int		i;
	int		amount;
	char	syntax;

	i = 0;
	syntax = input->input[0];
	ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
	ft_putstr_fd(" near unexpected token ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	if (syntax == '<')
		amount = 3;
	else
		amount = 2;
	while (input->input[i] == syntax && amount > 0)
	{
		ft_putchar_fd(input->input[i], STDERR_FILENO);
		i++;
		amount--;
	}
	ft_putstr_fd("'\n", STDERR_FILENO);
}

/**
 * @file syntax_printers.c
 * @brief Functions for printing syntax errors.
*/
void	next_is_null_error(t_shelldata *data)
{
	ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
	ft_putendl_fd(" near unexpected token `newline'", STDERR_FILENO);
	clear_input(data->input_list, SUCCESS);
	data->exit_value = 258;
}

/**
 * @brief checks the split data for syntax errors
 * @param data The data to be checked.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
int	check_split(t_shelldata *data)
{
	t_input_list	*temp;

	temp = data->input_list;
	while (temp != NULL)
	{
		if (ft_strchr("<>|", temp->input[0]) != NULL)
		{
			if (temp->next && ft_strchr("<>|", temp->next->input[0]) != NULL)
			{
				print_syntax_error(temp->next);
				clear_input(data->input_list, SUCCESS);
				data->exit_value = 258;
				return (FAILURE);
			}
			else if (temp->next == NULL && temp->input[0] != '|')
			{
				next_is_null_error(data);
				return (FAILURE);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
