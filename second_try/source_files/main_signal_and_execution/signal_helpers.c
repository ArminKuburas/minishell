/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:07:25 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/13 18:54:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file signal_helpers.c
 * @brief Helper functions for the signal handling.
*/

/**
 * @brief sets up child signals
 * @param void
 * @return void
*/

// void	baby_sigquit(int sig)
// 	{
// 	if (sig == SIGQUIT)
// 	{
// 		//write(1, "Quit: 3", 8);
// 		ft_putstr_fd("Quit: 3", STDOUT_FILENO);
// 	}
// 	ft_putstr_fd("\n", STDOUT_FILENO);
// 	}

void	child_signals(void)
{
	caret_switch(1);
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief sets up heredoc signals
 * @param void
 * @return void
*/

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief sets up standby signals
 * @param void
 * @return void
*/

void	standby_signals(void)
{
	caret_switch(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

/**
 * @brief sets up signals for the main shell
 * @param void
 * @return void
*/

void	handler_signals(void)
{
	caret_switch(0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

/**
 * @brief turns off signals
 * @param void
 * @return void
*/

void	signals_off(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
