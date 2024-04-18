/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:13:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/18 09:36:21 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_quote_found(t_split_data *data)
{
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
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		{
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
	while (data->i < data->len)
	{
		while (data->input[data->i] == ' ' && data->quote == '\0')
			data->i++;
		if (data->input[data->i] == '\0')
			break ;
		data->word_count++;
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
		{
			if (parser_quote_found(data) != SUCCESS)
				return (NO_QUOTE);
		}
		else if (ft_strchr("><|", data->input[data->i]) != NULL)
		{
			if (special_char_found(data, 0) != SUCCESS)
				return (FAILURE);
		}
		else if (space_found(data) != SUCCESS)
			return (NO_QUOTE);
	}
	return (SUCCESS);
}
