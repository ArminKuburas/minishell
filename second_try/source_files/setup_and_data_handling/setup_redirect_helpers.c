/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirect_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:04:51 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 07:05:29 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file setup_redirect_helpers.c
 * @brief Helper functions for setting up redirections.
*/

/**
 * @brief handles ambigious redirect
 * @param data The data to be used.
 * @param i The index of the child data.
 * @param input The input to be used.
 * @return void
*/

void	ambiguous_redirect(t_shelldata *data, int i, t_input_list *input)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(input->old_input, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	data->child_data[i].exit_value = 1;
}
