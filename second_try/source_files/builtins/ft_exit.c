/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 18:37:01 by tvalimak         ###   ########.fr       */
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

int	ft_exit(t_shelldata *data, char **inputs)
{
	int		i;
	int		exit_value;

	i = 0;
	exit_value = 0;
	if (inputs[1] != NULL)
	{
		if (inputs[2] != NULL)
		{
			ft_putendl_fd("bananashell: exit: too many arguments", 2);
			return (1);
		}
		while (inputs[1][i] != '\0')
		{
			if (ft_isdigit(inputs[1][i]) == 0)
			{
				ft_putendl_fd("bananashell: exit: numeric argument required", 2);
				return (1);
			}
			i++;
		}
		exit_value = ft_atoi(inputs[1]);
	}
	data->exit_value = exit_value;
	ft_putendl_fd("exit", 1);
	exit(exit_value);
	return (0);
}