/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_data_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:47:30 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 06:36:50 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file child_data_helpers.c
 * @brief Functions for handling child data.
*/

/**
 * @brief child failed. Frees all child data and exits.
 * @param child_data The child data to be used.
 * @param error The error code.
 * @return void
*/

void	child_failed(t_shelldata *data, int error)
{
	int	i;

	i = 0;
	if (error == NO_PIPE)
		ft_putstr_fd("minishell: pipe failed\n", 2);
	else if (error == NO_FORK)
		ft_putstr_fd("minishell: fork failed\n", 2);
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
		i++;
	}
	clear_input(data->input_list, FAILURE);
	free(data->input);
	clear_env_list(data->env_list, FAILURE);
	free(data->env_variables);
	rl_clear_history();
	exit(1);
}
