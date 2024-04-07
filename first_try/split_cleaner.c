/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/08 00:33:58 by akuburas         ###   ########.fr       */
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
	printf("Inside length_find_env\n");
	printf("Str: %s\n", str);
	while (env[i] != NULL)
	{
		printf("Env[%d]: %s\n", i, env[i]);
		if (ft_strncmp(env[i], str, n) == 0)
		{
			printf("Found env: %s\n", env[i]);
			while (env[i][j] != '=')
				j++;
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
		printf("Start: %d\n", start);
		printf("Split_input[%d][%d]: %c\n", i, *j, data->split_input[i][(*j)]);
		printf("Start character equals: %c\n", data->split_input[i][start]);
		while (ft_strchr(" \t$", data->split_input[i][(*j)]) == NULL)
			(*j)++;
		printf("End: %d\n", *j);
		length += length_find_env(data->env_variables,
				&data->split_input[i][start], (*j) - start);
		printf("After length_find_env\n");
		printf("Length: %d\n", length);
		return (length);
	}
	(*j)--;
	return (1);
}

int	new_length(t_shelldata *data, int i)
{
	int		j;
	char	quote;
	int		length;

	j = 0;
	quote = 'a';
	printf("inside new_length\n");
	length = 0;
	while (data->split_input[i][j] != '\0')
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
			{
				quote = data->split_input[i][j];
				printf("Quote found: %c\n", data->split_input[i][j]);
			}
			else if (quote == data->split_input[i][j])
			{
				printf("End quote found: %c\n", data->split_input[i][j]);
				quote = 'a';
			}
			else
			{
				printf("Inside quote: %c\n", data->split_input[i][j]);
				length++;
				printf("Length: %d\n", length);
			}
		}
		else if (data->split_input[i][j] != '$')
		{
			printf("No dollar: %c\n", data->split_input[i][j]);
			length++;
			printf("Length: %d\n", length);
		}
		else
		{
			printf("Dollar found: %c\n", data->split_input[i][j]);
			length += found_dollar(data, i, &j, quote);
			printf("Length: %d\n", length);
		}
		if (data->split_input[i][j] != '\0')
			j++;
	}
	return (length);
}

char	*find_env(char **env, char *str, int n)
{
	int	i;

	i = 0;
	printf("Inside find_env\n");
	printf("Str: %s\n", str);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, n) == 0)
		{
			printf("Found env: %s\n", env[i]);
			return (env[i]);
		}
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
	printf("Inside copy_dollar\n");
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
			printf("Env_array: %s\n", env_array);
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

	new_string = ft_calloc(length + 1, sizeof(char));
	if (new_string == NULL)
		return (NO_MEMORY);
	printf("inside allocate_new_string\n");
	printf("Length: %d\n", length);
	printf("Split_input[%d]: %s\n", i, data->split_input[i]);
	printf("Size of new_string: %lu\n", sizeof(new_string));
	printf("Size of char: %lu\n", sizeof(char));
	j = 0;
	new_i = 0;
	quote = 'a';
	while (new_i < length && data->split_input[i][j] != '\0')
	{
		if (ft_strchr("'\"", data->split_input[i][j]) != NULL)
		{
			if (quote == 'a')
			{
				printf("found quote\n");
				printf("data->split_input[%d][%d]: %c\n", i, j, data->split_input[i][j]);
				quote = data->split_input[i][j];
				printf("Quote: %c\n", quote);
			}
			else if (quote == data->split_input[i][j])
			{
				printf("found end quote\n");
				printf("data->split_input[%d][%d]: %c\n", i, j, data->split_input[i][j]);
				quote = 'a';
			}
			else
			{
				printf("inside quote\n");
				printf("Quote: %c\n", quote);
				printf("Split_input[%d][%d]: %c\n", i, j, data->split_input[i][j]);
				new_string[new_i] = data->split_input[i][j];
				printf("New_string[%d]: %c\n", new_i, new_string[new_i]);
				new_i++;
			}
		}
		else if (data->split_input[i][j] != '$')
		{
			printf("inside no dollar\n");
			printf("Split_input[%d][%d]: %c\n", i, j, data->split_input[i][j]);
			new_string[new_i] = data->split_input[i][j];
			printf("New_string[%d]: %c\n", new_i, new_string[new_i]);
			new_i++;
		}
		else if (quote != '\'')
		{
			printf("inside dollar\n");
			printf("Split_input[%d][%d]: %c\n", i, j, data->split_input[i][j]);
			printf("New_i: %d\n", new_i);
			new_i += copy_dollar(data, i, &j, &new_string[new_i]);
			printf("After copy_dollar\n");
			printf("New_string[%d]: %c\n", new_i, new_string[new_i]);
			printf("New_i: %d\n", new_i);
		}
		else
		{
			printf("last else statement dollar but single quotes\n");
			new_string[new_i] = data->split_input[i][j];
			printf("New_string[%d]: %c\n", new_i, new_string[new_i]);
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
	int	i;
	int	length;

	i = 0;
	printf("inside split_cleaner\n");
	while (data->split_input[i] != NULL)
	{
		length = new_length(data, i);
		printf("After new_length\n");
		printf("Length: %d\n", length);
		printf("Split_input[%d]: %s\n", i, data->split_input[i]);
		if ((size_t)length != ft_strlen(data->split_input[i]))
		{
			if (allocate_new_string(data, length, i) != SUCCESS)
			{
				printf("Memory Failure");
				free_double_array(&data->split_input);
				return (NO_MEMORY);
			}
		}
		i++;
	}
	return (SUCCESS);
}
