/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner_dollar_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:35:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/24 14:23:53 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file split_cleaner_dollar_functions.c
 * @brief Functions for handling dollar signs.
*/

/**
 * @brief Compares the environment variable name to the string.
 * @param env The environment variable name.
 * @param str The string to be compared.
 * @param len The length of the string.
*/
t_env_list	*try_to_find_env(t_env_list *env, char *str, int len)
{
	t_env_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strlen(temp->env_var_name) != (size_t)len)
		{
			temp = temp->next;
			continue ;
		}
		if (env_str_cmpr(temp->env_var_name, str, len) == 0)
			return (temp);
		if (temp != NULL)
			temp = temp->next;
	}
	return (NULL);
}

/**
 * @brief Copies the environment variable value to the new string.
 * @param data The data struct.
 * @param start The starting index of the string.
*/
void	copy_find_env(t_new_string_data *data, int start)
{
	int			j;
	t_env_list	*temp_env;

	temp_env = try_to_find_env(data->env, &data->temp->input[start],
			data->j - start);
	if (temp_env != NULL)
	{
		j = 0;
		while (temp_env->env_var_value[j])
		{
			data->new_string[data->i] = temp_env->env_var_value[j];
			data->i++;
			j++;
		}
	}
}

/**
 * @brief Copies the dollar sign to the new string.
 * @param data The data struct.
*/
void	copy_dollar(t_new_string_data *data)
{
	int		start;

	if (ft_strchr(" \t$'\"%", data->temp->input[data->j + 1]) == NULL)
	{
		data->j++;
		start = data->j;
		while (ft_strchr(" \t$'\"?%", data->temp->input[data->j]) == NULL)
			data->j++;
		if (data->temp->input[data->j] == '?' && start == data->j)
			data->j++;
		copy_find_env(data, start);
		data->j--;
		return ;
	}
	else if (ft_strchr("'\"%", data->temp->input[data->j + 1]) == NULL
		|| data->quote != 'a')
	{
		data->new_string[data->i] = data->temp->input[data->j];
		data->i++;
	}
}
