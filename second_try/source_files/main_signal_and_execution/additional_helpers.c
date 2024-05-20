/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:18:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/20 12:30:31 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file additional_helpers.c
 * @brief Additional helper functions for the main file.
*/

/**
 * @brief Helper function for the main loop.
 * @param data The data to be used.
 * @return void
*/
void	loop_helper(t_shelldata *data)
{
	handler_signals();
	data->input = readline("bananashell-0.32: ");
	if (!data->input)
		end_of_file_reached(data);
	if (create_exit_value_env(data) != SUCCESS)
	{
		free(data->input);
		rl_clear_history();
		ft_putendl_fd("error: memory allocation failed", STDERR_FILENO);
		exit(1);
	}
}
