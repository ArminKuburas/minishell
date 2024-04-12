/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner_dollar_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:35:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/12 07:53:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*try_to_find_env(t_env_list *env, char *str, int len)
{
	t_env_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strlen(temp->env_var_name) != len)
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

int	copy_find_env(t_env_list *env, char *str, int len, t_input_list *temp)
{
	int			i;
	t_env_list	*temp_env;

	temp_env = try_to_find_env(env, str, len);
	if (temp_env != NULL)
	{
		i = 0;
		while (temp_env->env_var_value[i])
			i++;
		return (i);
	}
	return (0);
}

int	copy_dollar(t_new_string_data *data)
{
	int		start;
	int		length;

	length = 1;
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		data->j++;
		start = data->j;
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		length = copy_find_env(data, start);
		data->j--;
	}
	return (length);
}


int	old_copy_dollar(t_shelldata *data, int i, int *j, char *new_string)
{
	int		start;
	char	*env_array;
	int		u;
	int		new_i;

	env_array = NULL;
	new_i = 0;
	if (ft_strchr(" \t$'\"", data->split_input[i][(*j) + 1]) == NULL)
	{
		(*j)++;
		start = *j;
		while (ft_strchr(" \t$'\"", data->split_input[i][*j]) == NULL)
			(*j)++;
		env_array = find_env(data->env_variables,
				&data->split_input[i][start], (*j) - start);
		if (env_array != NULL)
		{
			u = 0;
			while (env_array[u] != '=')
				u++;
			u++;
			while (env_array[u])
			{
				new_string[new_i] = env_array[u];
				u++;
				new_i++;
			}
			(*j)--;
		}
	}
	return (new_i);
}
