/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 19:27:42 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// If exit is called with a numeric argument, the shell exits with that specific exit status.
// This exit status should be an integer in the range of 0 to 255.

/*
bash-3.2$ exit donkey
exit
bash: exit: donkey: numeric argument required
*/

/*The range of 0 to 255 provides a wide range of values to differentiate between different types of errors or failure conditions.
While the exact meaning of each non-zero exit status can vary depending on the application or script, programmers often assign specific
exit codes to different types of errors to facilitate error handling and debugging.*/

int exit_handler(t_shelldata *data, char **inputs)
{
	int		exit_value;

	exit_value = 0;
	if (data->exit_value != 0)
		exit_value = data->exit_value;
	if (inputs[1] != NULL)
	{
		if (inputs[2] != NULL)
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("bananashell: exit: too many arguments", 2);
			exit_value = 1;
			return (exit_value);
		}
		while (inputs[1][exit_value] != '\0')
		{
			if (ft_isdigit(inputs[1][exit_value]) == 0)
			{
				ft_putendl_fd("bananashell: exit: numeric argument required", 2);
				exit_value = 255;
				return (exit_value);
			}
			exit_value++;
		}
		exit_value = ft_atoi(inputs[1]);
	}
	return (exit_value);
}

int	ft_exit(t_shelldata *data, char **inputs)
{
	int		i;
	int		exit_value;

	i = 0;
	exit_value = exit_handler(data, inputs);
	data->exit_value = exit_value;
	ft_putendl_fd("exit", 1);
	exit(exit_value);
	return (0);
}
