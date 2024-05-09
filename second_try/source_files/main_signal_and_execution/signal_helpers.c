/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:07:25 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/09 11:12:12 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	child_signals(void)
{
	caret_switch(1);
	signal(SIGINT, child_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	standby_signals(void)
{
	caret_switch(1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	handler_signals(void)
{
	caret_switch(0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

void	signals_off(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
