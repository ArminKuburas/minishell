/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:24:02 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/24 14:29:14 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file cd_helpers.c
 * @brief Helper functions for ft_cd.
*/

/**
 * @brief Changes the pwd string.
 * @param data The struct containing shell data.
 * @param temp The temp string used to modify path string.
 * @param path The path string to be checked.
 * @return success or failure.
*/
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

/**
 * @brief Changes working directory to one in given path.
 * @param data The struct containing shell data.
 * @param path The path string to be checked.
 * @return success or failure.
*/
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
