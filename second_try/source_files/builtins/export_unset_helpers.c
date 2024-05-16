/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:51:55 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/15 12:08:00 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	export_no_commands(t_shelldata *data, int fd)
{
	t_env_list		*temp;

	temp = data->env_list;
	if (!temp)
		return ;
	while (temp)
	{
		if (temp->env_var_name[0] != '?')
		{
			if (temp->env_var_value != NULL)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(temp->env_var_name, fd);
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(temp->env_var_value, fd);
				ft_putstr_fd("\"\n", fd);
			}
			else
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putendl_fd(temp->env_var_name, fd);
			}
		}
		temp = temp->next;
	}
}

int	is_unset_var_name_valid(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '_' && !ft_isalpha(input[i]))
	{
		ft_putstr_fd("bananashell: unset: `", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (FAILURE);
	}
	while (input[i] != '\0' && input[i] != '=')
	{
		if (ft_isalnum(input[i]) || input[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("bananashell: unset: `", STDERR_FILENO);
			ft_putstr_fd(input, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
