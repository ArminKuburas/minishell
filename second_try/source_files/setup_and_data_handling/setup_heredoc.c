/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:01 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/11 22:11:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	modification_loop(char *break_line, t_shelldata *data, int fd)
{
	char	*input_line;
	char	*modified_input;

	while (1)
	{
		input_line = readline("> ");
		if (!input_line)
			break ;
		if (ft_strcmp(input_line, break_line) == 0)
		{
			free(input_line);
			break ;
		}
		modified_input = modify_input(input_line, data->env_list);
		free(input_line);
		if (modified_input == NULL)
		{
			close(fd);
			child_failed(data, NO_MEMORY);
		}
		ft_putendl_fd(modified_input, fd);
		free(modified_input);
	}
}

char	*heredoc_cleaner(char *input)
{
	char	*cleaned_input;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr("'\"", input[i]) == NULL)
			j++;
		i++;
	}
	cleaned_input = ft_calloc(j + 1, sizeof(char));
	if (cleaned_input == NULL)
		return (NULL);
	i = 0;
	while (i < j || input[i] != '\0')
	{
		if (ft_strchr("'\"", input[i]) == NULL)
			cleaned_input[i] = input[i];
		i++;
	}
	return (cleaned_input);
}

void	unmodified_loop(char *break_line, int fd)
{
	char	*input_line;

	while (1)
	{
		input_line = readline("> ");
		if (!input_line)
			break ;
		if (ft_strcmp(input_line, break_line) == 0)
		{
			free(input_line);
			break ;
		}
		ft_putendl_fd(input_line, fd);
		free(input_line);
	}
}

static void	write_loop(int fd, t_input_list *input, t_shelldata *data)
{
	char	*break_line;
	int		modification_needed;

	modification_needed = YES;
	if (input->old_input == NULL)
		break_line = ft_strdup(input->input);
	else
	{
		if (ft_strchr(input->old_input, '\'')
			|| ft_strchr(input->old_input, '"'))
			modification_needed = NO;
		break_line = heredoc_cleaner(input->old_input);
	}
	if (break_line == NULL)
		child_failed(data, NO_MEMORY);
	if (modification_needed == YES)
		modification_loop(break_line, data, fd);
	else
		unmodified_loop(break_line, fd);
}

void	handle_heredoc(t_shelldata *data, int i, t_input_list *input)
{
	int		pipe_fd[2];

	if (data->child_data[i].exit_value != 0)
		return ;
	if (input->word_split == WORD_SPLIT
		|| ((ft_strcmp(input->input, "") == 0 && input->old_input[0] == '$')))
	{
		ambiguous_redirect(data, i, input);
		return ;
	}
	if (pipe(pipe_fd) == -1)
		child_failed(data, NO_PIPE);
	data->child_data[i].fd_in = pipe_fd[0];
	write_loop(pipe_fd[1], input, data);
	close(pipe_fd[1]);
}