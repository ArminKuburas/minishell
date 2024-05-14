/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_split_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 07:34:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 16:34:33 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file potential_split_functions.c
 * @brief Functions for handling potential splits.
 */

/**
 * @brief Checks if the string is a potential split.
 * @param data The data to be used.
 * @return Returns 1 if the string is a potential split, 0 if not.
 */
bool	check_string(t_new_string_data *data)
{
	int	start;

	start = data->j;
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		if (data->temp->input[data->j] == '$'
			&& ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) != NULL)
		{
			data->j = start;
			copy_dollar(data);
			return (1);
		}
		data->j = start;
		return (0);
	}
	copy_dollar(data);
	return (1);
}

/**
 * @brief Checks if the given string needs to be split.
 * @param temp_env The environment variable to be checked.
 * @return Returns YES if the string needs to be split, NO if not.
 */
int	check_if_split_needed(t_env_list *temp_env)
{
	int	i;

	i = 0;
	while (temp_env->env_var_value[i] != '\0')
	{
		if (ft_strchr(" \t", temp_env->env_var_value[i]) != NULL)
			return (YES);
		i++;
	}
	return (NO);
}

/**
 * @brief Finds the environment variable.
 * @param data The data to be used.
 * @param split_check The check if the string needs to be split.
 * @return Returns the environment variable.
 */
t_env_list	*potential_find_env(t_new_string_data *data, bool *split_check)
{
	int			start;
	t_env_list	*temp_env;

	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		data->j++;
		start = data->j;
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		temp_env = try_to_find_env(data->env, &data->temp->input[start],
				data->j - start);
		if (temp_env != NULL)
		{
			if (check_if_split_needed(temp_env) == YES)
				*split_check = 1;
			else
				data->j = start - 1;
		}
		return (temp_env);
	}
	return (NULL);
}

/**
 * @brief Creates the new nodes needed.
 * @param data The data to be used.
 */
void	potential_split_create(t_new_string_data *data)
{
	t_env_list	*temp_env;
	bool		split_check;

	if (check_string(data) == 1)
		return ;
	split_check = 0;
	temp_env = potential_find_env(data, &split_check);
	if (split_check == 0 && temp_env != NULL)
		copy_dollar(data);
	else if (split_check == 1)
		split_env(data, temp_env);
}
