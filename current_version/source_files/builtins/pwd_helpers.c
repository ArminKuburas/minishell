/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:41:53 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/26 14:42:24 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file cd_helpers.c
 * @brief Helper functions for ft_cd.
*/

/**
 * @brief Updates the PWD variable in the env list.
 * @param data The struct containing shell data.
 * @param temp_env Node to be modified.
 * @return success or failure.
*/
int	env_var_update(t_env_list *temp_env, t_shelldata *data, int flag)
{
	free(temp_env->env_var_value);
	if (flag == 0)
	{
		temp_env->env_var_value = ft_strdup(data->pwd);
		if (!temp_env->env_var_value)
			return (NO_MEMORY);
		temp_env->env_var = ft_strjoin("PWD=", temp_env->env_var_value);
	}
	else
	{
		temp_env->env_var_value = ft_strdup(data->old_pwd);
		if (!temp_env->env_var_value)
			return (NO_MEMORY);
		temp_env->env_var = ft_strjoin("OLDPWD=", temp_env->env_var_value);
	}
	if (!temp_env->env_var)
		return (NO_MEMORY);
	return (SUCCESS);
}
