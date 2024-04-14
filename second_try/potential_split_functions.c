/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_split_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 07:34:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/14 23:07:05 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*This function checks to see if the given $string ends with a $ character
 that is followed by nothing.
 The reason this is important is because it prevents a split from happening
 example: $TEMP="Hello World"
 If in the shell you call it like this: > $TEMP$
 it views it as one long string: Hello World$
 The space included in the string.*/
bool	check_string(t_new_string_data *data)
{
	int	start;

	start = data->j;
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		while (ft_strchr(" \t$'\"", data->temp->input[data->j] == NULL))
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

t_env_list	potential_find_env(t_new_string_data *data, bool *split_check)
{
	int			start;
	t_env_list	*temp_env;
	int			j;

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
			{
				*split_check = 1;
				return (*temp_env);
			}
			else
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
	}
}

void	potential_split_create(t_new_string_data *data)
{
	t_env_list	*temp_env;
	bool		split_check;

	if (check_string(data) == 1)
		return ;
	split_check = 0;
	temp_env = potential_find_env(data, &split_check);
	if (split_check == 0 || temp_env != NULL)
		copy_dollar(data);
	else if (split_check == 1)
		split_env(data, temp_env);
}
