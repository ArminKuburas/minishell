/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:33:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 17:11:13 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	new_env_node(t_env_list *old_node, char *env_name, char *env_value)
{
	t_env_list	*new_node;
	char		*temp;

	new_node = ft_calloc(1, sizeof(t_env_list));
	if (!new_node)
		return (NO_MEMORY);
	old_node->next = new_node;
	new_node->env_var_name = env_name;
	new_node->env_var_value = env_value;
	temp = ft_strjoin(env_name, "=");
	if (!temp)
		return (NO_MEMORY);
	new_node->env_var = ft_strjoin(temp, env_value);
	free(temp);
	if (!new_node->env_var)
		return (NO_MEMORY);
	return (SUCCESS);
}

int	create_question_node(t_shelldata *data, t_env_list *temp)
{
	char	*env_var_name;

	env_var_name = ft_strdup("?");
	if (!env_var_name)
		return (NO_MEMORY);
	return (new_env_node(temp, env_var_name, ft_itoa(data->exit_value)));
}

int	create_exit_value_env(t_shelldata *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->env_var_name, "?") == 0)
		{
			free (temp->env_var_value);
			temp->env_var_value = ft_itoa(data->exit_value);
			if (!temp->env_var_value)
				return (NO_MEMORY);
			return (SUCCESS);
		}
		if (temp->next == NULL)
			return (create_question_node(data, temp));
		temp = temp->next;
	}
	return (FAILURE);
}

int	initial_env_creation(char **env, t_shelldata *data)
{
	int	error;

	error = duplicate_env(env, data);
	if (error != SUCCESS)
		return (FAILURE);
	error = update_shell_level(data);
	if (error != SUCCESS)
	{
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	error = create_exit_value_env(data);
	if (error != SUCCESS)
	{
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	initial_setup(t_shelldata *data, int argc, char **argv, char **env)
{
	if (check_argc_argv(argc, argv) == FAILURE)
		return (FAILURE);
	if (env)
		if (initial_env_creation(env, data) == FAILURE)
			return (FAILURE);
	data->pwd = getcwd(NULL, 0);
	if (!data->pwd)
	{
		ft_putendl_fd("getcwd has failed", 2);
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}
