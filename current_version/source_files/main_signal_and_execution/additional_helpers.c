/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:18:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/24 16:24:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file additional_helpers.c
 * @brief Additional helper functions for the main file.
*/

/**
 * @brief Resets the signals to default.
 * @return void
*/
void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief This is an initial check for the input.
 * @param data The data to be checked.
 * @return Returns SUCCESS if the input is valid, otherwise FAILURE.
*/
int	initial_check(t_shelldata *data)
{
	int	i;

	i = 0;
	if (data->input == NULL)
		return (FAILURE);
	if (ft_strlen(data->input) == 0)
		return (FAILURE);
	while (data->input[i] != '\0')
	{
		if (ft_strchr(" \t", data->input[i]) == NULL)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

/**
 * @brief cleans up everything before reaching the end of file.
 * @param data The data to be cleaned up.
 * @return void
*/
static void	end_of_file_reached(t_shelldata *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	clear_env_list(data->env_list, SUCCESS);
	free(data->pwd);
	free(data->env_variables);
	rl_clear_history();
	signal_reset();
	if (data->exit_value != 0)
		exit (1);
	exit(0);
}

/**
 * @brief Helper function for the main loop.
 * @param data The data to be used.
 * @return void
*/
void	loop_helper(t_shelldata *data)
{
	handler_signals();
	data->input = readline("minishell: ");
	if (!data->input)
		end_of_file_reached(data);
	if (create_exit_value_env(data) != SUCCESS)
	{
		free(data->input);
		rl_clear_history();
		ft_putendl_fd("error: memory allocation failed", STDERR_FILENO);
		signal_reset();
		exit(1);
	}
}
