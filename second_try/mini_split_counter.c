/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:13:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/11 11:09:16 by akuburas         ###   ########.fr       */
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
		ft_putstr_fd("Error: No closing quote found\n", 2);
		return (NO_QUOTE);
	}
	(*i)++;
	return (SUCCESS);
}

static int	special_char_found(char *input, int *i, int *word_count)
{
	(*word_count)++;
	(*i)++;
	if (ft_strchr("><", input[*i]) != NULL
		&& input[*i] == input[*i - 1])
	{
		(*i)++;
		if (ft_strchr("><|", input[*i]) != NULL)
		{
			printf("Error: Syntax error\n");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	space_found(char *input, int *i, int len, int *word_count)
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
			if (special_char_found(input, i, word_count) != SUCCESS)
				return (FAILURE);
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
