/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:22:59 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/08 18:26:45 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
env_var = HOME=/Users/tvalimak
env_var_name = HOME
env_var_value = /Users/tvalimak
*/

static char	*ret_env(t_shelldata *data, char *var)
{
	while (data->env_list)
	{
		if (ft_strcmp(data->env_list->env_var_name, var) == 0)
			return (data->env_list->env_var_value);
		data->env_list = data->env_list->next;
	}
	return (NULL);
}

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

int	ft_cd(t_shelldata *data, char **inputs)
{
	if (!inputs[1] || (ft_strncmp(inputs[1], "~", 2) == 0))
	{
		cd_home(data, "HOME");
		return (SUCCESS);
	}
	if (inputs[1] && ft_strncmp(inputs[1], "..", 3) == 0)
	{
		if (chdir("..") == -1)
			return (FAILURE);
		refresh_pwd(data);
	}
	else
		path_parser(data, inputs[1]);
	return (SUCCESS);
}

// chdir("/Users/tvalimak/minitalk_two");
// is how the chdir can be called with a absolute path
