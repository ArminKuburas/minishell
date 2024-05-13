/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:43:48 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/13 18:27:08 by tvalimak         ###   ########.fr       */
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

/*void	child_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}*/

void	parent_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		//write(1, "Quit: 3", 8);
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
		//exit(0);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
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
