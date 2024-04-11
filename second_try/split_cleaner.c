/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/11 13:46:30 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*find_env(char **env, char *str, int n)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, n) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	copy_dollar(t_shelldata *data, int i, int *j, char *new_string)
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

int	allocate_new_string(t_shelldata *data, int length, int i)
{
	char	*new_string;
	int		j;
	char	quote;
	int		new_i;

	new_string = ft_calloc(length + 1, sizeof(char));
	if (new_string == NULL)
		return (NO_MEMORY);
	j = 0;
	new_i = 0;
	quote = 'a';
	while (new_i < length && data->split_input[i][j] != '\0')
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
			{
				quote = data->split_input[i][j];
			}
			else if (quote == data->split_input[i][j])
			{
				quote = 'a';
			}
			else
			{
				new_string[new_i] = data->split_input[i][j];
				new_i++;
			}
		}
		else if (data->split_input[i][j] != '$')
		{
			new_string[new_i] = data->split_input[i][j];
			new_i++;
		}
		else if (quote != '\'')
			new_i += copy_dollar(data, i, &j, &new_string[new_i]);
		else
		{
			new_string[new_i] = data->split_input[i][j];
			new_i++;
		}
		j++;
	}
	new_string[j] = '\0';
	free(data->split_input[i]);
	data->split_input[i] = new_string;
	return (SUCCESS);
}

int	split_cleaner(t_shelldata *data)
{
	size_t			length;
	t_input_list	*temp;

	temp = data->input_list;
	while (temp != NULL)
	{
		length = new_length(temp, data->env_variables);
		if (length != ft_strlen(data->input_list))
		{
			if (allocate_new_string(data, length, i) != SUCCESS)
			{
				clear_input(data->input_list, NO_MEMORY);
				return (NO_MEMORY);
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
