/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:51:55 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/24 14:35:00 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file export_unset_helpers.c
 * @brief Helper functions for the export and unset builtin.
*/

/**
 * @brief If unset PWD is done, this checks that .
 * @param data The struct containing shell data.
 * @param input The input to be replaced.
*/
int	pwd_unset_check(t_shelldata *data, char *input)
{
	if (ft_strncmp(input, "PWD", 4) == 0)
	{
		if (check_if_unset_env_exists(data, input) == YES)
		{
			data->cd_used = 0;
			remove_from_env_list(data, input);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

/**
 * @brief Checks that is cd used when exporting PWD to set
 * 		  the correct path as its value.
 * @param data The struct containing shell data.
 * @param input The input to be checked if its "PWD".
*/
int	pwd_check(t_shelldata *data, char *input)
{
	char	*path;

	if (ft_strncmp(input, "PWD", 4) == 0)
	{
		if (check_if_export_env_exists(data, input) == NO && data->cd_used == 1)
		{
			path = ft_strjoin("=", data->pwd);
			if (path == NULL)
				return (NO_MEMORY);
			input = ft_strjoin(input, path);
			if (input == NULL)
				return (NO_MEMORY);
			if (path)
				free (path);
			add_new_env_var(data, input, 0, 1);
			if (input)
				free (input);
			data->cd_used = 0;
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

/**
 * @brief Prints the env list as export format.
 * @param data The struct containing shell data.
 * @param fd The file descriptor to be used.
*/
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

/**
 * @brief Checks that the input given to unset is a valid variable name.
 * @param data The struct containing shell data.
 * @param fd The file descriptor to be used.
*/
int	is_unset_var_name_valid(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '_' && !ft_isalpha(input[i]))
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
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
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(input, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
