/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:07:25 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/18 09:35:34 by akuburas         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_handler);
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
