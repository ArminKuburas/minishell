/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:22:59 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/10 14:38:49 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	cd_home(t_shelldata *data, char *cmd)
{
	t_env_list	*env_head;
	char		*home_path;

	env_head = data->env_list;
	home_path = ret_env(data, cmd);
	data->env_list = env_head;
	if (home_path == NULL)
		ft_putendl_fd("bananashell: cd: HOME not set", 2);
	if (chdir(home_path) == -1)
		return (FAILURE);
	refresh_pwd(data);
	return (SUCCESS);
}

int	path_parser(t_shelldata *data, char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("bananashell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (FAILURE);
	}
	refresh_pwd(data);
	return (SUCCESS);
}

int	cd_parent_directory(t_shelldata *data)
{
	char	*temp;

	if (chdir("..") == 0)
	{
		refresh_old_pwd(data);
		temp = data->pwd;
		data->pwd = getcwd(NULL, 0);
		if (data->pwd == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access", 2);
			ft_putendl_fd("parent directories: No such file or directory", 2);
			data->pwd = ft_strjoin(temp, "/..");
			if (data->pwd == NULL)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		update_env_pwd(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	cd_current_directory(t_shelldata *data)
{
	char	*temp;

	if (chdir(".") == 0)
	{
		refresh_old_pwd(data);
		temp = data->pwd;
		data->pwd = getcwd(NULL, 0);
		if (data->pwd == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access", 2);
			ft_putendl_fd("parent directories: No such file or directory", 2);
			data->pwd = ft_strjoin(temp, "/.");
			if (data->pwd == NULL)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		update_env_pwd(data);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_cd(t_shelldata *data, char **inputs)
{
	int	return_value;

	return_value = 0;
	if (!inputs[1] || (ft_strncmp(inputs[1], "~", 2) == 0))
	{
		return_value = cd_home(data, "HOME");
		if (return_value == FAILURE)
			return (FAILURE);
		return_value = refresh_pwd(data);
		return (return_value);
	}
	else if (inputs[1] && ft_strncmp(inputs[1], "..", 3) == 0)
		return_value = cd_parent_directory(data);
	else if (inputs[1] && ft_strncmp(inputs[1], ".", 3) == 0)
		return_value = cd_current_directory(data);
	else
		return_value = path_parser(data, inputs[1]);
	return (return_value);
}
