/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:31:08 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 18:57:44 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	free_with_newline(char **temp, int fd)
{
	int	i;

	i = 1;
	while (temp[i])
	{
		ft_putstr_fd(temp[i], fd);
		if (temp[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
}

void	print_no_newline(t_child_data *data, int fd, int i)
{
	while (ft_strcmp(data->command_inputs[i], "-n") == 0)
	{
		if (data->command_inputs[i] == NULL)
			return ;
		i++;
	}
	while (data->command_inputs[i])
	{
		ft_putstr_fd(data->command_inputs[i], fd);
		if (data->command_inputs[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
}

int	ft_echo(t_child_data *data, int fd)
{
	int	i;

	i = 1;
	if (data->command_inputs[i] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (SUCCESS);
	}
	if (ft_strcmp(data->command_inputs[i], "-n") == 0)
		print_no_newline(data, fd, i);
	else
		free_with_newline(data->command_inputs, fd);
	return (SUCCESS);
}
