/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:44:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/30 16:31:20 by akuburas         ###   ########.fr       */
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

int	space_found(char *input, int *i, int len)
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
		else if (space_found(input, &i, len) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	duplicate_quote(char *input, t_shelldata *data, int j, int e)
{
	char	quote;

	quote = input[j];
	data->split_input[e] = ft_strchr(input + j + 1, quote);
	data->split_input[e] = ft_strndup(input + j,
			data->split_input[e] - input - j + 1);
}

void	duplicate_input(char *input, t_shelldata *data, int j, int e)
{
	int	i;

	i = j;
	while (input[j] != ' ' && input[j] != '\0')
		j++;
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
			return (NO_MEMORY);
		j += ft_strlen(data->split_input[e]);
		e++;
	}
	data->split_input[e] = NULL;
	return (SUCCESS);
}

/* This function is used to split the given input into seperate lines.
These will later be filtered into the parser.
In addition it returns an error value if something fails.*/
int	mini_split(char *input, t_shelldata *data)
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
	return (SUCCESS);
}
