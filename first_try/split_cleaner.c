/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/04 19:06:35 by akuburas         ###   ########.fr       */
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
	if (ft_strchr(" \t$", data->split_input[i][(*j) + 1]) == NULL)
	{
		(*j)++;
		start = *j;
		while (ft_strchr(" \t$", data->split_input[i][(*j)]) == NULL)
			(*j)++;
		length += length_find_env(data->env_variables,
				&data->split_input[i][(*j)], start - (*j));
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
	if (ft_strchr(" \t$", data->split_input[i][(*j) + 1]) == NULL)
	{
		(*j)++;
		start = *j;
		while (ft_strchr(" \t$", data->split_input[i][*j]) == NULL)
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

	new_string = malloc((length + 1) * sizeof(char));
	if (new_string == NULL)
		return (NO_MEMORY);
	printf("inside allocate_new_string\n");
	printf("Length: %d\n", length);
	printf("Split_input[%d]: %s\n", i, data->split_input[i]);
	printf("Size of new_string: %lu\n", sizeof(new_string));
	printf("Size of *char: %lu\n", sizeof(char));
	j = 0;
	new_i = 0;
	quote = 'a';
	while (new_i < length)
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
				quote = data->split_input[i][j];
			else if (quote == data->split_input[i][j])
				quote = 'a';
			else
				new_string[new_i] = data->split_input[i][j];
		}
		else if (data->split_input[i][j] != '$')
			new_string[new_i] = data->split_input[i][j];
		else if (quote != '\'')
			new_i += copy_dollar(data, i, &j, &new_string[new_i]);
		else
			new_string[new_i] = data->split_input[i][j];
		new_i++;
		j++;
	}
	new_string[j] = '\0';
	free(data->split_input[i]);
	data->split_input[i] = new_string;
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
		printf("inside split_cleaner\n");
		printf("Length: %d\n", length);
		printf("Split_input[%d]: %s\n", i, data->split_input[i]);
		if ((size_t)length == ft_strlen(data->split_input[i]))
		{
			i++;
			continue ;
		}
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
