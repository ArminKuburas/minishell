/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:13:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/18 11:19:46 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	space_found(t_split_data *data);

int	parser_quote_found(t_split_data *data)
{
	printf("inside parser quote found\n");
	if (data->quote == '\0')
		data->quote = data->input[data->i];
	else if (data->quote == data->input[data->i])
		data->quote = '\0';
	while (data->input && data->input[data->i] != data->quote)
		data->i++;
	if (data->input[data->i] == data->quote)
		data->quote = '\0';
	else
	{
		ft_putstr_fd("Error: No closing quote found\n", 2);
		return (NO_QUOTE);
	}
	if (ft_strchr(" \t", data->input[data->i + 1]) == NULL)
	{
		data->i++;
		space_found(data);
	}
	return (SUCCESS);
}

static int	special_char_found(t_split_data *data, int check)
{
	printf("Inside special_char_found\n");
	if (check == 1)
		data->word_count++;
	data->i++;
	if (ft_strchr("><", data->input[data->i]) != NULL
		&& data->input[data->i] == data->input[data->i - 1])
	{
		data->i++;
		if (ft_strchr("><|", data->input[data->i]) != NULL)
		{
			printf("bananashell: Syntax error near unexpected token\n");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	space_found(t_split_data *data)
{
	printf("inside space_found\n");
	while (data->i < data->len && data->input[data->i] != ' ')
	{
		printf("inside space found loop\n");
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		{
			printf("quote found while in space found\n");
			if (parser_quote_found(data) != SUCCESS)
				return (NO_QUOTE);
		}
		else if (data->input[data->i] == '\0')
			break ;
		else if (ft_strchr("><|", data->input[data->i]) != NULL)
		{
			if (special_char_found(data, 1) != SUCCESS)
				return (FAILURE);
			break ;
		}
		if (data->input[data->i] != '\0')
			data->i++;
	}
	return (SUCCESS);
}

int	count_words(t_split_data	*data)
{
	printf("Inside count words\n");
	while (data->i < data->len)
	{
		printf("Inside while loop of count words\n");
		while (data->input[data->i] == ' ' && data->quote == '\0')
			data->i++;
		if (data->input[data->i] == '\0')
			break ;
		data->word_count++;
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		{
			printf("Inside first if statement. quotes found\n");
			if (parser_quote_found(data) != SUCCESS)
				return (NO_QUOTE);
		}
		else if (ft_strchr("><|", data->input[data->i]) != NULL)
		{
			printf("inside else if statement. special chars\n");
			if (special_char_found(data, 0) != SUCCESS)
				return (FAILURE);
		}
		else if (space_found(data) != SUCCESS)
			return (NO_QUOTE);
		if (data->input[data->i] != '\0')
			data->i++;
	}
	return (SUCCESS);
}
