/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:22:59 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/24 12:28:16 by tvalimak         ###   ########.fr       */
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

int	path_joiner(t_shelldata *data, char *temp, char *path)
{
	int	i;

	i = 0;
	while (temp[i + 1] != '\0')
		i++;
	if (temp[i] != '/')
		temp = ft_strjoin(temp, "/");
	if (temp == NULL)
		return (FAILURE);
	data->pwd = ft_strjoin(temp, path);
	if (data->pwd == NULL)
	{
		return (FAILURE);
		ft_putendl_fd("Fail in strdup, inside pwd", 2);
	}
	return (SUCCESS);
}

int	change_dir(t_shelldata *data, char *path)
{
	char	*temp;

	if (chdir(path) == 0)
	{
		refresh_old_pwd(data);
		temp = data->pwd;
		data->pwd = getcwd(NULL, 0);
		if (data->pwd == NULL)
		{
			ft_putstr_fd("cd: error retrieving current directory: ", 2);
			ft_putstr_fd("getcwd: cannot access", 2);
			ft_putendl_fd("parent directories: No such file or directory", 2);
			if (path_joiner(data, temp, path) == FAILURE)
				return (NO_MEMORY);
			update_env_pwd(data);
			data->cd_used = 1;
			return (FAILURE);
		}
		update_env_pwd(data);
		data->cd_used = 1;
		return (SUCCESS);
	}
	return (FAILURE);
}

/**
 * @brief Checks if the given path is accessible and cd's there.
 * @param data The struct containing shell data.
 * @param path The path string to be checked.
 * @return void
*/
int	path_parser(t_shelldata *data, char *path)
{
	int	error_value;

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
		error_value = change_dir(data, path);
		return (error_value);
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
			if (path_joiner(data, temp, "..") == FAILURE)
				return (FAILURE);
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
			if (path_joiner(data, temp, ".") == FAILURE)
				return (FAILURE);
		}
		update_env_pwd(data);
		data->cd_used = 1;
		return (SUCCESS);
	}
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
