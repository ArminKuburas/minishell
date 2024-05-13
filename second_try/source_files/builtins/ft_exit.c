/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/12 14:11:22 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clean_exit(t_shelldata *data, int flag)
{
	if (flag)
		ft_putendl_fd("exit", 2);
	handler_signals();
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
