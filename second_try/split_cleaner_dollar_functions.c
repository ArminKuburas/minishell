/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner_dollar_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:35:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/14 14:55:44 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	copy_find_env(t_new_string_data *data, int start)
{
	int			j;
	t_env_list	*temp_env;

	printf("Inside copy find env\n");
	printf("data->j - start = %d\n", data->j - start);
	temp_env = try_to_find_env(data->env, &data->temp->input[start],
			data->j - start);
	if (temp_env != NULL)
	{
		j = 0;
		printf("Found env\n");
		printf("Env name: %s\n", temp_env->env_var_name);
		printf("Env value: %s\n", temp_env->env_var_value);
		printf("data->new_string: %s\n", data->new_string);
		printf("data new string[i]: %c\n", data->new_string[data->i]);
		while (temp_env->env_var_value[j])
		{
			data->new_string[data->i] = temp_env->env_var_value[j];
			data->i++;
			j++;
		}
	}
}

void	copy_dollar(t_new_string_data *data)
{
	int		start;

	printf("Inside copy dollar\n");
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		data->j++;
		start = data->j;
		printf("Start: %d\n", start);
		printf("Input[j]: %c\n", data->temp->input[data->j]);
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		printf("End: %d\n", data->j);
		printf("Input[j]: %c\n", data->temp->input[data->j]);
		copy_find_env(data, start);
		data->j--;
		return ;
	}
	data->new_string[data->i] = data->temp->input[data->j];
	data->i++;
}
