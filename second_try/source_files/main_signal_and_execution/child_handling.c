/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:52:53 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 10:59:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	child_handling(t_shelldata *data)
{
	int	error;
	//We need to do proper error handling here.
	child_pre_check(data);
	error = create_exit_value_env(data);
	if (error != SUCCESS)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd("Malloc failed", STDERR_FILENO);
		clear_input(data->input_list, FAILURE);
		clear_env_list(data->env_list, FAILURE);
		free(data->env_variables);
		free(data->input);
		rl_clear_history();
		exit(1);
	}
}
