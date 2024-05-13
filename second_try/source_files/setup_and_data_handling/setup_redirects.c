/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 20:33:18 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_redirects.c
 * @brief Functions for setting up redirections.
 */

/**
 * @brief Redirects input from a file.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
 */
static void	redirect_input(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_in != 0)
		close(data->child_data[i].fd_in);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		ambiguous_redirect(data, i, input);
		return ;
	}
	data->child_data[i].fd_in = open(input->input, O_RDONLY, 0777);
	if (data->child_data[i].fd_in == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->child_data[i].exit_value = 1;
	}
	else if (data->child_data[i].fd_in == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->child_data[i].exit_value = 1;
	}
}

/**
 * @brief Redirects output to a file.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
 */
static void	redirect_output(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_out != 0)
		close(data->child_data[i].fd_out);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		ambiguous_redirect(data, i, input);
		return ;
	}
	data->child_data[i].fd_out
		= open(input->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->child_data[i].fd_out == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->child_data[i].exit_value = 1;
	}
	else if (data->child_data[i].fd_out == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->child_data[i].exit_value = 1;
	}
}

/**
 * @brief Redirects append to a file.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
 */
static void	redirect_append(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_out != 0)
		close(data->child_data[i].fd_out);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		ambiguous_redirect(data, i, input);
		return ;
	}
	data->child_data[i].fd_out = open(input->input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->child_data[i].fd_out == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->child_data[i].exit_value = 1;
	}
	else if (data->child_data[i].fd_out == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->child_data[i].exit_value = 1;
	}
}

/**
 * @brief Sets up redirections.
 * @param data The data to be used.
 * @param index The index of the child data.
 * @return void
 */
void	setup_redirects(t_shelldata *data, int index)
{
	t_input_list	*temp;
	int				i;

	temp = data->input_list;
	i = index;
	while (i > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		i--;
	}
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT_INPUT)
			redirect_input(data, index, temp->next);
		if (temp->type == REDIRECT_OUTPUT)
			redirect_output(data, index, temp->next);
		if (temp->type == REDIRECT_APPEND)
			redirect_append(data, index, temp->next);
		if (temp->type == REDIRECT_HEREDOC)
			handle_heredoc(data, index, temp->next);
		temp = temp->next;
	}
}
