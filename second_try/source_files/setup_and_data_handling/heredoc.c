/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:14:23 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 14:19:00 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	heredoc_child(t_shelldata data, t_input_list *temp)
{
	int		fd;
	//char	*file;
	char	*line;

	(void)data;
	heredoc_signals();
	//file = ft_strjoin(data.pwd, "/heredoc");
	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putendl_fd("Failed to open file in heredoc", 2);
		exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, temp->input) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(0);
}

void	heredoc(t_shelldata data, t_input_list *temp)
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("Fork failed in heredoc", 2);
		exit(1);
	}
	standby_signals();
	if (pid == 0)
		heredoc_child(data, temp);
	waitpid(pid, &data.exit_value, 0);
	handler_signals();
}
