/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:22:59 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/23 15:18:19 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_cd.c
 * @brief Built-in cd function.
*/

/**
 * @brief Checks the exit value of the child process.
 * @param child_data The child data to be used.
 * @param already_printed If the exit value has already been printed.
 * @return void
*/
static int	cd_home(t_shelldata *data, char *cmd)
{
	t_env_list	*env_head;
	char		*home_path;

	env_head = data->env_list;
	home_path = ret_env(data, cmd);
	data->env_list = env_head;
	if (home_path == NULL)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	if (chdir(home_path) == -1)
		return (FAILURE);
	refresh_pwd(data);
	data->cd_used = 1;
	return (SUCCESS);
}

/**
 * @brief Checks if the given path is accessible and cd's there.
 * @param data The struct containing shell data.
 * @param path The path string to be checked.
 * @return void
*/
int	path_parser(t_shelldata *data, char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(path, STDERR_FILENO);
			ft_putendl_fd(": Permission denied", STDERR_FILENO);
			return (FAILURE);
		}
		if (cd_check_if_directory(path) == NO)
			return (FAILURE);
		chdir(path);
		refresh_pwd(data);
		data->cd_used = 1;
		return (SUCCESS);
	}
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (FAILURE);
}

/**
 * @brief cds to the parent directory
 * @param data The struct containing shell data.
 * @return success or failure.
*/
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
			free(temp);
			if (data->pwd == NULL)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		update_env_pwd(data);
		data->cd_used = 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

/**
 * @brief cds to the current directory.
 * @param data The struct containing shell data.
 * @return success or failure.
*/
int	cd_current_directory(t_shelldata *data)
{
	char	*temp;

	printf("inside cd_current_directory\n");
	if (chdir(".") == 0)
	{
		refresh_old_pwd(data);
		printf("after refresh_old_pwd\n");
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
		data->cd_used = 1;
		return (SUCCESS);
	}
	printf("returning failure\n");
	return (FAILURE);
}

/**
 * @brief The main cd function.
 * @param data The struct containing shell data.
 * @param inputs The inputs to be used.
 * @return success or failure.
*/
int	ft_cd(t_shelldata *data, char **inputs)
{
	int	return_value;

	return_value = 0;
	printf("inside ft_cd\n");
	if (!inputs[1] || (ft_strncmp(inputs[1], "~", 2) == 0))
	{
		printf("inside if\n");
		return_value = cd_home(data, "HOME");
		if (return_value == FAILURE)
			return (FAILURE);
		return_value = refresh_pwd(data);
		printf("after refresh_pwd\n");
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
