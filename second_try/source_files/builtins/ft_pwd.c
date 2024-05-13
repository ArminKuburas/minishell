/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 17:19:00 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ret_env(t_shelldata *data, char *var)
{
	while (data->env_list)
	{
		if (ft_strcmp(data->env_list->env_var_name, var) == 0)
			return (data->env_list->env_var_value);
		data->env_list = data->env_list->next;
	}
	return (NULL);
}

void	update_env_pwd(t_shelldata *data)
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
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		if (ft_strcmp(temp->env_var_name, "OLDPWD") == 0)
		{
			free(temp->env_var_value);
			temp->env_var_value = ft_strdup(data->old_pwd);
			if (!temp->env_var_value)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		temp = temp->next;
	}
}

void	refresh_old_pwd(t_shelldata *data)
{
	if (data->old_pwd)
		free(data->old_pwd);
	data->old_pwd = ft_strdup(data->pwd);
	if (!data->old_pwd)
		ft_putendl_fd("Fail in strdup, inside pwd", 2);
	update_env_pwd(data);
}

int	refresh_pwd(t_shelldata *data)
{
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->pwd)
	{
		data->old_pwd = ft_strdup(data->pwd);
		if (!data->old_pwd)
		{
			ft_putendl_fd("Fail in strdup, inside pwd", 2);
			return (FAILURE);
		}
	}
	if (data->pwd)
		free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putendl_fd("Fail in getcwd, inside pwd", 2);
		return (FAILURE);
	}
	update_env_pwd(data);
	return (SUCCESS);
}

int	ft_pwd(char *pwd, int fd)
{
	if (!pwd)
	{
		ft_putendl_fd("Fail in getcwd, inside pwd", 2);
		return (FAILURE);
	}
	ft_putendl_fd(pwd, fd);
	return (SUCCESS);
}
