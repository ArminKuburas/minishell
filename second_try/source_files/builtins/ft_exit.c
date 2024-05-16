/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 14:01:41 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_exit.c
 * @brief Functions for builtin exit command.
*/

/**
 * @brief cleans all allocated data before exiting the program.
 * @param data main struct for the program.
*/
void	exit_cleaner(t_shelldata *data)
{
	int	i;

	free(data->input);
	free(data->env_variables);
	clear_input(data->input_list, SUCCESS);
	free(data->pwd);
	clear_env_list(data->env_list, SUCCESS);
	i = 0;
	while (i < data->command_amount)
	{
		free_child_data(&data->child_data[i]);
		i++;
	}
	free(data->child_data);
}

/**
 * @brief fully exits the program with teh given exit value.
 * @param data main struct for the program.
 * @param flag if 1, prints exit message.
*/
void	clean_exit(t_shelldata *data, int flag)
{
	if (flag)
		ft_putendl_fd("exit", 2);
	handler_signals();
	exit_cleaner(data);
	exit(data->exit_value);
}

/**
 * @brief checks if the given input is a valid exit command.
 * @param data main struct for the program.
 * @param inputs array of strings from the input.
*/
int	ft_exit(t_shelldata *data, char **inputs)
{
	if (!inputs[1])
	{
		data->exit_value = 0;
		clean_exit(data, 1);
		return (data->exit_value);
	}
	check_format(data, inputs);
	return (data->exit_value);
}
