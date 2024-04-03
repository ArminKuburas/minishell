/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:44:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/03 19:16:00 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_found(char *input, int *i, int len)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (*i < len && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
	{
		printf("Error: No closing quote found\n");
		return (NO_QUOTE);
	}
	(*i)++;
	return (SUCCESS);
}

int	space_found(char *input, int *i, int len, int *word_count)
{
	while (*i < len && input[*i] != ' ')
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			if (quote_found(input, i, len) != SUCCESS)
				return (NO_QUOTE);
		}
		else if (input[*i] == '\0')
			break ;
		else if (ft_strchr("><|", input[*i]) != NULL)
		{
			(*word_count)++;
			(*i)++;
			if (ft_strchr("><", input[*i]) != NULL &&
				input[*i] == input[*i - 1])
			{
				(*i)++;
				if (ft_strchr("><|", input[*i]) != NULL)
				{
					printf("Error: Syntax error\n");
					return (FAILURE);
				}
			}
			break ;
		}
		(*i)++;
	}
	return (SUCCESS);
}

int	count_words(char *input, int *word_count)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		while (i < len && input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		(*word_count)++;
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote_found(input, &i, len) != SUCCESS)
				return (NO_QUOTE);
		}
		else if (space_found(input, &i, len, word_count) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	duplicate_quote(char *input, t_shelldata *data, int j, int e)
{
	char	quote;
	int		i;
	int		k;
	char	*temp;
	char	*temp2;

	quote = input[j];
	if (quote == '\'')
	{
		data->split_input[e] = ft_strchr(input + j, quote);
		data->split_input[e] = ft_strndup(input + j,
				data->split_input[e] - input - j);
	}
	else
	{
		i = j;
		j++;
		while (input[j] != quote)
		{
			if (input[j] == '$' && ft_strchr(" \t\n\"", input[j + 1]) == NULL)
			{
				temp = ft_strndup(input + i + 1, j - i - 1);
				if (temp == NULL)
				{
					data->split_input[e] = NULL;
					return ;
				}
				find_env_variable(temp, data->env_variables);
				if (temp2 == NULL)
				{
					data->split_input[e] = NULL;
					return ;
				}
				data->split_input[e] = ft_strjoin(data->split_input[e], temp2);
				if (data->split_input[e] == NULL)
				{
					data->split_input[e] = NULL;
					return ;
				}
				free(temp);
				free(temp2);
				i = j;
			}
			j++;
		}
	}
}

void	duplicate_input(char *input, t_shelldata *data, int j, int e)
{
	int	i;

	i = j;
	if (ft_strchr("><|", input[j]) != NULL)
	{
		if (ft_strchr("><", input[j + 1]) != NULL && input[j] == input[j + 1])
		{
			if (ft_strchr("><|", input[j + 2]) != NULL)
			{
				printf("Error: Syntax error\n");
				data->split_input[e] = NULL;
			}
			else
				data->split_input[e] = ft_strndup(input + j, 2);
		}
		else
			data->split_input[e] = ft_strndup(input + j, 1);
		return ;
	}
	while (input[j] != ' ' && input[j] != '\0')
	{
		if (ft_strchr("><|", input[j]) != NULL)
			break ;
		j++;
	}
	data->split_input[e] = ft_strndup(input + i, j - i);
}

int	create_strings(char *input, t_shelldata *data, int word_count)
{
	int	j;
	int	e;

	j = 0;
	e = 0;
	while (e < word_count)
	{
		while (input[j] == ' ')
			j++;
		if (input[j] == '\0')
			break ;
		if (input[j] == '"' || input[j] == '\'')
			duplicate_quote(input, data, j, e);
		else
			duplicate_input(input, data, j, e);
		if (data->split_input[e] == NULL)
		{
			free_double_array(&data->split_input);
			return (NO_MEMORY);
		}
		j += ft_strlen(data->split_input[e]);
		e++;
	}
	data->split_input[e] = NULL;
	return (SUCCESS);
}

/* This function is used to split the given input into seperate lines.
These will later be filtered into the parser.
In addition it returns an error value if something fails.*/
int	mini_split(char *input, t_shelldata *data, char **env)
{
	int		word_count;

	word_count = 0;
	if (count_words(input, &word_count) != SUCCESS)
		return (FAILURE);
	data->split_input = (char **)malloc((word_count + 1) * sizeof(char *));
	if (data->split_input == NULL)
		return (NO_MEMORY);
	if (create_strings(input, data, word_count) != SUCCESS)
		return (FAILURE);
	if (split_cleaner(data, env) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
