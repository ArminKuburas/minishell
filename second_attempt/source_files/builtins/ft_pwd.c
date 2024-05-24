/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/23 15:29:54 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @brief Returns the value of the env variable.
 * @param data The struct containing shell data.
 * @param var The variable to be returned.
 * @return The env_value needed.
*/
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

/**
 * @brief Updates the PWD variable in the env lis.
 * @param data The struct containing shell data.
 * @return Returns void.
*/
void	update_env_pwd(t_shelldata *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	printf("before while\n");
	while (temp)
	{
		if (ft_strcmp(temp->env_var_name, "PWD") == 0)
		{
			printf("before free\n");
			free(temp->env_var_value);
			printf("before strdup\n");
			temp->env_var_value = ft_strdup(data->pwd);
			if (!temp->env_var_value)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		if (ft_strcmp(temp->env_var_name, "OLDPWD") == 0)
		{
			printf("before free\n");
			free(temp->env_var_value);
			temp->env_var_value = ft_strdup(data->old_pwd);
			if (!temp->env_var_value)
				ft_putendl_fd("Fail in strdup, inside pwd", 2);
		}
		temp = temp->next;
	}
}

/**
 * @brief Updates the OLD_PWD in the env list.
 * @param data The struct containing shell data.
 * @return Returns void.
*/
void	refresh_old_pwd(t_shelldata *data)
{
	if (data->old_pwd)
	{
		free(data->old_pwd);
		data->old_pwd = NULL;
	}
	printf("after free\n");
	if (data->pwd)
		data->old_pwd = ft_strdup(data->pwd);
	printf("after strdup\n");
	if (!data->old_pwd)
		ft_putendl_fd("Fail in strdup, inside pwd 5", 2);
	update_env_pwd(data);
	printf("after update_env_pwd\n");
}

/**
 * @brief Updates the PWD's in the data struct and the env list.
 * @param data The struct containing shell data.
 * @return Returns void.
*/
int	refresh_pwd(t_shelldata *data)
{
	if (data->old_pwd)
	{
		free(data->old_pwd);
		data->old_pwd = NULL;
	}
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
		ft_putendl_fd("Fail in getcwd, inside pwd 1", 2);
		return (FAILURE);
	}
	update_env_pwd(data);
	return (SUCCESS);
}

/**
 * @brief Prints the current working directory.
 * @param pwd The current working directory.
 * @param fd The file descriptor.
*/
int	ft_pwd(char *pwd, int fd)
{
	if (!pwd)
	{
		ft_putendl_fd("Fail in getcwd, inside pwd 2", 2);
		return (FAILURE);
	}
	ft_putendl_fd(pwd, fd);
	return (SUCCESS);
}
