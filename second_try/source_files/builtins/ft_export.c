/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:01 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/14 02:27:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_export.c
 * @brief Built-in export function.
*/

/**
 * @brief Checks if the export variable name is valid.
 * @param input The input to be checked.
 * @return Returns 0 if successful, 1 if not.
 
*/
static int	is_export_var_name_valid(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '_' && !ft_isalpha(input[i]))
	{
		ft_putstr_fd("bananashell: export: `", STDERR_FILENO);
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
			ft_putstr_fd("bananashell: export: `", STDERR_FILENO);
			ft_putstr_fd(input, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

/**
 * @brief compares the env var name to the input
 * @param env_var_name The env var name.
 * @param input The input to be compared.
 * @param i The index of the input.
 * @return Returns yes or no answer.
*/
int	compare_env_var_name(char *env_var_name, char *input, int i)
{
	if (ft_strlen(env_var_name) != (size_t)i)
		return (NO);
	if (ft_strncmp(env_var_name, input, i) == 0)
		return (YES);
	else
		return (NO);
}

/*This one goes through the env list and sees if the new env var
  already exists*/
/**
 * @brief Checks if the export env exists.
 * @param data The struct containing shell data.
 * @param input The input to be checked.
 * @return Returns yes or no answer.
*/
static int	check_if_export_env_exists(t_shelldata *data, char *input)
{
	int			i;
	t_env_list	*temp_env;

	i = 0;
	while (input[i] && input[i] != '=')
		i++;
	temp_env = data->env_list;
	while (temp_env)
	{
		if (compare_env_var_name(temp_env->env_var_name, input, i) == YES)
			return (YES);
		temp_env = temp_env->next;
	}
	return (NO);
}

/*  This function will go through the input list and figures out do we
    replace or add the new key/value pair */
/**
 * @brief Executes the export command.
 * @param data The struct containing shell data.
 * @param input The input to be executed.
 * @return Returns 0 if successful, 1 if not.
*/
static int	execute_export_command(t_shelldata *data, char *input)
{
	char	*value_index;

	value_index = ft_strchr(input, '=');
	if (value_index != NULL)
	{
		if (check_if_export_env_exists(data, input) == YES)
			return (replace_env_var(data, input, 0, 1));
		else
			return (add_new_env_var(data, input, 0, 1));
	}
	else
	{
		if (check_if_export_env_exists(data, input) == YES)
			return (SUCCESS);
		else
			return (add_new_env_var(data, input, 0, 0));
	}
	return (SUCCESS);
}

/* my_export main function*/
/**
 * @brief The export built-in function.
 * @param data The struct containing shell data.
 * @param inputs The inputs to be exported.
 * @param fd The file descriptor.
 * @return Returns 0 if successful, 1 if not.
*/
int	ft_export(t_shelldata *data, char **inputs, int fd)
{
	int	i;
	int	return_value;

	i = 1;
	return_value = SUCCESS;
	if (inputs[i] == NULL)
	{
		export_sorted_list(data->env_list);
		export_no_commands(data, fd);
		return (return_value);
	}
	while (inputs[i] != NULL)
	{
		if (is_export_var_name_valid(inputs[i]) == SUCCESS)
			execute_export_command(data, inputs[i]);
		else
			return_value = FAILURE;
		i++;
	}
	create_2d_env(data);
	return (return_value);
}
