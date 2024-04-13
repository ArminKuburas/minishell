/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:43:48 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/12 17:31:23 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int signal, t_handler handler)
{
	struct sigaction	action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	if (sigaction(signal, &action, 0) < 0)
		printf("sigaction error\n"); // Make this proper whenever we get error function
}

void	parent_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_handler(SIGINT, sigint_handler);
	signal_handler(SIGQUIT, SIG_IGN);
	signal_handler(SIGTTIN, SIG_IGN);
	signal_handler(SIGTTOU, SIG_IGN);
	signal_handler(SIGTSTP, SIG_IGN);
}

/*Old signal handler for safekeep
called from main like this:
		//set_state(HANDLER);
		//set_state(DEFAULT);
		//signal(SIGINT, signal_handler);
		//signal(SIGQUIT, signal_handler);
*/

// void standby_signals(void)
// void fork_signals(void)
/*
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	carrot_toggle(int on)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	set_state(t_state state)
{
	if (state == DEFAULT)
	{
		carrot_toggle(1);
	}
	if (state == HEREDOC)
	{
		return ;
	}
	if (state == HANDLER)
	{
		carrot_toggle(0);
	}
}*/