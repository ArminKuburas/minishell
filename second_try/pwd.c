/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:10:36 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/22 20:43:47 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*This function refreshes the pwd and old_pwd information, it should be called every
  time pwd changes. It also updates the same information in the env's*/
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

void	my_pwd(t_shelldata data, t_input_list *temp)
{
	(void)temp;
	ft_putendl_fd(data.pwd, 1);
}
