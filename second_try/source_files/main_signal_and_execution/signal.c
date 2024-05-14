/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:43:48 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/14 15:28:39 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file signal.c
 * @brief Signal handling functions.
*/

/**
 * @brief Handles the SIGINT signal.
 * @param sig The signal number.
 * @return void
*/
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief child signal handler for SIGINT
 * @param sig The signal number.
 * @return void
*/
void	child_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

/**
 * @brief parent signal handler for SIGINT
 * @param sig The signal number.
 * @return void
*/
void	parent_sigint(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
 * @brief Handles the SIGQUIT signal.
 * @param sig The signal number.
 * @return void
*/
void	heredoc_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

/**
 * @brief Switches the caret on or off.
 * @param on 1 to turn on, 0 to turn off.
 * @return void
*/
void	caret_switch(int on)
{
	struct termios	term;

	term = (struct termios){0};
	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
