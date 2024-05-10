/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:43:48 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/10 15:17:39 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	child_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	parent_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	caret_switch(int on)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
