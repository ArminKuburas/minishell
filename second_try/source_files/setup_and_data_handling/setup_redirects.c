/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 12:57:56 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_ambiguous_redirect(t_shelldata *data, int i, t_input_list *input)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input->old_input, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	data->child_data[i].exit_value = 1;
}

/*  this function attempts to redirect input from a file
It first confirms if it can access and open the given input_file.
It not it sets the correct exit_value (error value)*/
static void	redirect_input(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_in != 0)
		close(data->child_data[i].fd_in);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		handle_ambiguous_redirect(data, i, input);
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

static void	redirect_output(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_out != 0)
		close(data->child_data[i].fd_out);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		handle_ambiguous_redirect(data, i, input);
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

static void	redirect_append(t_shelldata *data, int i, t_input_list *input)
{
	if (data->child_data[i].exit_value != 0)
		return ;
	if (data->child_data[i].fd_out != 0)
		close(data->child_data[i].fd_out);
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		handle_ambiguous_redirect(data, i, input);
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

void	write_loop(int fd, t_input_list *input)
{
	char	*line;

	if (input->word_split == WORD_SPLIT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->old_input, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return ;
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	handle_heredoc(t_shelldata *data, int i, t_input_list *input)
{
	int		pipe_fd[2];

	if (data->child_data[i].exit_value != 0)
		return ;
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		handle_ambiguous_redirect(data, i, input);
		return ;
	}
	if (pipe(pipe_fd) == -1)
		child_failed(data, NO_PIPE);
	data->child_data[i].fd_in = pipe_fd[0];
	write_loop(pipe_fd[1], input);
	close(pipe_fd[1]);
}

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
