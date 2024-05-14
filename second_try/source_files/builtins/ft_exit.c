/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 05:43:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

void	clean_exit(t_shelldata *data, int flag)
{
	if (flag)
		ft_putendl_fd("exit", 2);
	handler_signals();
	exit_cleaner(data);
	exit(data->exit_value);
}

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
