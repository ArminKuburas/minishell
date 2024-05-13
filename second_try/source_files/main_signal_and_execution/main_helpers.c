/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:33:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 17:47:08 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file main_helpers.c
 * @brief Helper functions for the main file.
 * @details This file contains helper functions for the main file.
*/

/**
 * @brief Creates a new node in the env list.
 * @param old_node The node to be connected to the new node.
 * @param env_name The name of the environment variable.
 * @param env_value The value of the environment variable.
 * @return Returns SUCCESS if everything went well, otherwise NO_MEMORY.
*/

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

/**
 * @brief Creates a new node for the exit value.
 * @param data The data to be used.
 * @param temp The temporary node to be connected to the new node.
 * @return Returns SUCCESS if everything went well, otherwise NO_MEMORY.
*/

int	create_question_node(t_shelldata *data, t_env_list *temp)
{
	char	*env_var_name;

	env_var_name = ft_strdup("?");
	if (!env_var_name)
		return (NO_MEMORY);
	return (new_env_node(temp, env_var_name, ft_itoa(data->exit_value)));
}

/**
 * @brief Creates the exit value environment variable.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise NO_MEMORY.
*/

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

/**
 * @brief Duplicates the environment variables.
 * @param env The environment variables to be duplicated.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/

int	initial_env_creation(char **env, t_shelldata *data)
{
	int	error;


	int i = 0;
	while (env[i])
	{
		printf ("env[%d] = %s\n", i, env[i]);
		i++;
	}
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

/**
 * @brief Sets up the initial data for the minishell.
 * @param data The data to be set up.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param env The environment variables.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/

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
