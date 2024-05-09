/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:01 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/09 17:19:51 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*heredoc_cleaner(char *input)
{
	char	*cleaned_input;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr("'\"", input[i]) == NULL)
			i++;
	}
	cleaned_input = ft_calloc(i + 1, sizeof(char));
	if (cleaned_input == NULL)
		return (NULL);
	i = 0;
	while (input[i] == '\0')
	{
		if (ft_strchr("'\"", input[i]) == NULL)
			cleaned_input[i] = input[i];
		i++;
	}
	return (cleaned_input);
}

void	modification_loop(char *break_line, t_shelldata *data)
{
	char	*input_line;
	char	*modified_input;

	while (1)
	{
		input_line = readline("modified> ");
		if (!input_line)
			break ;
		if (ft_strcmp(input_line, break_line) == 0)
		{
			free(input_line);
			break ;
		}
		modified_input = modify_input(input_line);
		if (modified_input == NULL)
			child_failed(data, NO_MEMORY);
		write(data->child_data->fd_in, modified_input, ft_strlen(modified_input));
		free(input_line);
		free(modified_input);
	}
}

static void	write_loop(int fd, t_input_list *input, t_shelldata *data)
{
	char	*input_line;
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
		modification_loop(break_line, data);
	else
	{
		while (1)
		{
			input_line = readline("> ");
			if (!input_line)
				break ;
			write(fd, input_line, ft_strlen(input_line));
			write(fd, "\n", 1);
			free(input_line);
		}
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
		ambiguous_redirect(data, i, input);
		return ;
	}
	if (pipe(pipe_fd) == -1)
		child_failed(data, NO_PIPE);
	data->child_data[i].fd_in = pipe_fd[0];
	write_loop(pipe_fd[1], input, data);
	close(pipe_fd[1]);
}