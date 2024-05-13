/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_counter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:13:40 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 20:27:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file mini_split_counter.c
 * @brief Functions for counting words in the input.
*/

static int	space_found(t_split_data *data);

/**
 * @brief Checks if a quote is found and sets the quote variable.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise NO_QUOTE.
*/
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
	if (ft_strchr(" \t", data->input[data->i + 1]) == NULL)
	{
		data->i++;
		space_found(data);
	}
	return (SUCCESS);
}

/**
 * @brief Checks if a special character is found.
 * @param data The data to be used.
 * @param check The check variable.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/
static int	special_char_found(t_split_data *data, int check)
{
	if (check == 1)
		data->word_count++;
	data->i++;
	if (ft_strchr("><", data->input[data->i]) != NULL
		&& data->input[data->i] == data->input[data->i - 1])
	{
		data->i++;
		if (ft_strchr("><|", data->input[data->i]) != NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Checks if a space is found.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise NO_QUOTE.
*/
static int	space_found(t_split_data *data)
{
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

/**
 * @brief Counts the words in the input.
 * @param data The data to be used.
 * @return Returns SUCCESS if everything went well, otherwise NO_QUOTE.
*/
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
		if (data->input[data->i] != '\0')
			data->i++;
	}
	return (SUCCESS);
}