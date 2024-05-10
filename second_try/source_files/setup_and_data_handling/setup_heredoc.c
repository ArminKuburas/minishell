/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:01 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/10 12:18:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	found_dollar_sign(char *input, t_env_list *env_list, int *original_i)
{
	int			i;
	t_env_list *temp;

	temp = env_list;
	i = 0;
	while (input[i] != '\0' && ft_strchr(" \t\n$?", input[i]) == NULL)
		i++;
	if (i == 0 && input[i] == '?')
		i++;
	*original_i += i;
	while (temp != NULL)
	{
		if ((size_t)i == ft_strlen(temp->env_var_name))
		{
			if (ft_strncmp(input, temp->env_var_name, i) == 0)
				return (ft_strlen(temp->env_var_value));
		}
		temp = temp->next;
	}
	return (0);
}

int	modified_length(char *input, t_env_list *env_list)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			i++;
			length += found_dollar_sign(&input[i], env_list, &i);
		}
		else
			length++;
	}
	return (length);
}

void	set_up_new_input(char *input, char *new_input, t_env_list *env_list)
{
	int			i;
	int			j;
	t_env_list	*temp;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			i++;
			temp = env_list;
			while (temp != NULL)
			{
				if (ft_strncmp(&input[i], temp->env_var_name,
						ft_strlen(temp->env_var_name)) == 0)
				{
					ft_strlcpy(&new_input[j], temp->env_var_value,
						ft_strlen(temp->env_var_value) + 1);
					j += ft_strlen(temp->env_var_value);
					i += ft_strlen(temp->env_var_name);
					break ;
				}
				temp = temp->next;
			}
		}
		else
			new_input[j++] = input[i++];
	}
}

char	*modify_input(char *input, t_env_list *env_list)
{
	char	*new_input;

	new_input = ft_calloc(modified_length(input, env_list) + 1, sizeof(char));
	if (new_input == NULL)
		return (NULL);
	set_up_new_input(input, new_input, env_list);
	return (new_input);
}
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

void	modification_loop(char *break_line, t_shelldata *data, int fd)
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
		modification_loop(break_line, data, fd);
	else
	{
		while (1)
		{
			input_line = readline("> ");
			if (!input_line)
				break ;
			ft_putendl_fd(input_line, fd);
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