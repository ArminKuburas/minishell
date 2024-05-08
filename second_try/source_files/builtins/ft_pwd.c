/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 17:38:48 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	update_env_pwd(t_shelldata *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while (temp)
	{
		if (ft_strcmp(temp->env_var_name, "PWD") == 0)
		{
			free(temp->env_var_value);
			temp->env_var_value = ft_strdup(data->pwd);
			if (!temp->env_var_value)
				ft_putendl_fd("Fail in strdup, inside pwd", 2); // replace with proper error handling
		}
		if (ft_strcmp(temp->env_var_name, "OLDPWD") == 0)
		{
			free(temp->env_var_value);
			temp->env_var_value = ft_strdup(data->old_pwd);
			if (!temp->env_var_value)
				ft_putendl_fd("Fail in strdup, inside pwd", 2); // replace with proper error handling
		}
		temp = temp->next;
	}
}

void	refresh_pwd(t_shelldata *data)
{
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->pwd)
	{
		data->old_pwd = ft_strdup(data->pwd);
		if (!data->old_pwd)
			ft_putendl_fd("Fail in strdup, inside pwd", 2); // replace with proper error handling
	}
	if (data->pwd)
		free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
		ft_putendl_fd("Fail in getcwd, inside pwd", 2); // replace with proper error handling
	update_env_pwd(data);
}

int	ft_pwd(char *pwd)
{
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (SUCCESS);
}
