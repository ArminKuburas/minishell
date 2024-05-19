/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:01 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/19 20:12:17 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_heredoc.c
 * @brief Functions for setting up heredoc.
*/

/**
 * @brief Modifies the input line.
 * @param input_line The input line to be modified.
 * @param env_list The environment list.
 * @return Returns the modified input line.
*/
void	modification_loop(char *break_line, t_shelldata *data, int fd)
{
	char	*input;
	char	*modified_input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strlen(input) > 1
			&& ft_strncmp(input, break_line, ft_strlen(input) - 1) == 0)
		{
			free(input);
			break ;
		}
		modified_input = modify_input(input, data->env_list);
		free(input);
		if (modified_input == NULL)
		{
			close(fd);
			child_failed(data, NO_MEMORY);
		}
		ft_putstr_fd(modified_input, fd);
		free(modified_input);
	}
}

/**
 * @brief Cleans the input line.
 * @param input The input line to be cleaned.
 * @return Returns the cleaned input line.
*/
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

/**
 * @brief Handles the unmodified input line.
 * @param break_line The break line.
 * @param fd The file descriptor.
 * @return void
*/
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

/**
 * @brief Writes the input line.
 * @param fd The file descriptor.
 * @param input The input line.
 * @param data The data to be used.
 * @return void
*/
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
	free(break_line);
}

/**
 * @brief Handles the heredoc.
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input list.
 * @return void
*/
void	handle_heredoc(t_shelldata *data, int i, t_input_list *input)
{
	int		pipe_fd[2];
	int		dup_fd;

	if (data->child_data[i].exit_value != 0)
		return ;
	if (pipe(pipe_fd) == -1)
		child_failed(data, NO_PIPE);
	data->child_data[i].fd_in = pipe_fd[0];
	dup_fd = dup(STDIN_FILENO);
	heredoc_signals();
	write_loop(pipe_fd[1], input, data);
	close(pipe_fd[1]);
	dup2(dup_fd, STDIN_FILENO);
	handler_signals();
	close(dup_fd);
}
