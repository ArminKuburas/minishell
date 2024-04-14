/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:22:59 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/14 15:48:55 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
env_var = HOME=/Users/tvalimak
env_var_name = HOME
env_var_value = /Users/tvalimak
*/

static char	*ret_env(t_shelldata data, char *var)
{
	while (data.env_list)
	{
		if (ft_strcmp(data.env_list->env_var_name, var) == 0)
			return (data.env_list->env_var_value);
		data.env_list = data.env_list->next;
	}
	return (NULL);
}

static void	cd_old_pwd(t_shelldata data, char *cmd)
{

}

static void	cd_home(t_shelldata data, char *cmd)
{
	char	*home_path;

	home_path = ret_env(data, cmd);
	if (home_path == NULL)
		ft_printf("HOME PATH NOT SET\n");
	if (chdir(home_path) == -1)
	{
		ft_printf("ERROR IN CD_HOME\n");
		return ;
	}
	ft_printf("cd succeeded\n");
}

void	my_cd(t_shelldata data, t_input_list *temp)
{
	if (!temp->next || (ft_strncmp(temp->next->input, "~", 2) == 0))
	{
		// go to home dir
		cd_home(data, "HOME");
	}
	if (ft_strncmp(temp->next->input, "-", 2) == 0)
	{
		// go to old pwd
		cd_old_pwd(data, "OLD_PWD");
	}
}
