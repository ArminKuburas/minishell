/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 10:27:06 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/27 13:32:00 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_built_ins(t_shelldata *data, t_input_list *temp)
{
	ft_printf("got inside the executioner\n");
	if (temp->input == NULL)
		return (0);
	else if (ft_strncmp(temp->input, "export", 7) == 0)
		my_export(data, temp);
	else if (ft_strncmp(temp->input, "unset", 6) == 0)
		my_unset(data, temp);
	else if (ft_strncmp(temp->input, "cd", 3) == 0)
		my_cd(data, temp);
	else if (ft_strncmp(temp->input, "exit", 5) == 0)
		my_exit(data, temp);
	else if (ft_strncmp(temp->input, "env", 4) == 0)
		my_env(data);
	else if (ft_strncmp(temp->input, "pwd", 4) == 0)
		my_pwd(data, temp);
	else if (ft_strncmp(temp->input, "echo", 5) == 0)
		my_echo(temp);
	else
		return (0);
	return (1);
}
