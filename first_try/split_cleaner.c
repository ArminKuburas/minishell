/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/04 16:35:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_find_env(char **env, char *str, int n)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	length = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, n) == 0)
		{
			while (env[i][j] != '=')
				j++;
			while (env[i][j] != '\0')
			{
				j++;
				length++;
			}
			break ;
		}
		i++;
	}
	return (length);
}

int	found_dollar(t_shelldata *data, int i, int *j, char quote)
{
	int	length;
	int	start;

	length = 0;
	if (quote == '\'')
		return (1);
	if (ft_strchr(" \t$", data->split_input[i][*j + 1]) == NULL)
	{
		*(j++);
		start = *j;
		while (ft_strchr(" \t$", data->split_input[i][*j]) == NULL)
			*(j++);
		length += length_find_env(data->env_variables,
				data->split_input[i][*j], start - *j);
		return (length);
	}
	return (1);
}

int	new_length(t_shelldata *data, int i)
{
	int		j;
	char	quote;
	int		length;

	j = 0;
	quote = 'a';
	while (data->split_input[i][j])
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
				quote = data->split_input[i][j];
			else if (quote == data->split_input[i][j])
				quote = 'a';
			else
				length++;
		}
		else if (data->split_input[i][j] != '$')
			length++;
		else
			length += found_dollar(data, i, &j, quote);
		j++;
	}
	return (length);
}

void	copy_dollar(t_shelldata *data, int i, int *j, char *new_string)
{
	int		start;
	char	*env_array;
	int		u;

	env_array = NULL;
	if (ft_strchr(" \t$", data->split_input[i][*j + 1]) == NULL)
	{
		*(j++);
		start = *j;
		while (ft_strchr(" \t$", data->split_input[i][*j]) == NULL)
			*(j++);
		env_array = find_env(data->env_variables,
				data->split_input[i][start], *j - start);
		if (env_array != NULL)
		{
			u = 0;
			while (env_array[u] != '=')
				u++;
			u++;
			while (env_array[u])
			{
				new_string[i] = env_array[u];
				u++;
				i++;
			}
		}
	}
}

int	allocate_new_string(t_shelldata *data, int length, int i)
{
	char	*new_string;
	int		j;
	char	quote;

	new_string = malloc((length + 1) * sizeof(char));
	if (new_string == NULL)
		return (NO_MEMORY);
	j = 0;
	quote = 'a';
	while (j < length)
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
				quote = data->split_input[i][j];
			else if (quote == data->split_input[i][j])
				quote = 'a';
			else
				new_string[j] = data->split_input[j];
		}
		else if (data->split_input[i][j] != '$')
			new_string[j] = data->split_input[j];
		else if (quote != '\'')
			copy_dollar(data, i, &j, new_string);
		else
			new_string[j] = data->split_input[j];
		j++;
	}
	return (SUCCESS);
}

int	split_cleaner(t_shelldata *data)
{
	int	i;
	int	length;

	i = 0;
	while (data->split_input[i] != NULL)
	{
		
		length = new_length(data, i);
		if (allocate_new_string(data, length, i) != SUCCESS)
		{
			printf("Memory Failure");
			free_double_array(&data->split_input);
			return (NO_MEMORY);
		}
		i++;
	}
	return (SUCCESS);
}
