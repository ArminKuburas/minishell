/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_length_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:06:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/13 20:33:41 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file cleaner_length_functions.c
 * @brief Functions for finding the length of the cleaned input.
*/


/**
 * @brief Compares the environment variable name to the string.
 * @param env The environment variable name.
 * @param str The string to be compared.
 * @param len The length of the string.
*/
int	env_str_cmpr(char *env, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (env[i] != str[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Finds the length of the environment variable value.
 * @param env The environment list.
 * @param str The string to be compared.
 * @param len The length of the string.
*/
int	length_find_env(t_env_list *env, char *str, int len)
{
	t_env_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strlen(temp->env_var_name) != (size_t)len)
		{
			temp = temp->next;
			continue ;
		}
		if (env_str_cmpr(temp->env_var_name, str, len) == 0)
			return (ft_strlen(temp->env_var_value));
		if (temp != NULL)
			temp = temp->next;
	}
	return (0);
}

/**
 * @brief handles the case of when you find a dollar character
 * @param temp The input list.
 * @param i The index of the input list.
 * @param quote The quote character.
 * @param env The environment list.
 * @return The length of the environment variable value.
*/
int	found_dollar(t_input_list *temp, int *i, char quote, t_env_list *env)
{
	int	length;
	int	start;

	length = 0;
	if (quote == '\'')
		return (1);
	if (ft_strchr(" \t$'\"", temp->input[(*i) + 1]) == NULL)
	{
		(*i)++;
		start = *i;
		while (ft_strchr(" \t$'\"?", temp->input[(*i)]) == NULL)
			(*i)++;
		if (temp->input[*i] == '?' && start == *i)
			(*i)++;
		length += length_find_env(env, &temp->input[start], (*i) - start);
		(*i)--;
		if (quote == 'a')
			temp->word_split = POTENTIAL_SPLIT;
		temp->needs_cleaning = 1;
		return (length);
	}
	return (1);
}

/**
 * @brief Handles the case of when you find a quote character.
 * @param input The input character.
 * @param quote The quote character.
 * @param temp The input list.
*/
int	cleaner_quote_found(char input, char *quote, t_input_list *temp)
{
	temp->needs_cleaning = 1;
	if (*quote == 'a')
		*quote = input;
	else if (*quote == input)
		*quote = 'a';
	else
		return (1);
	return (0);
}

/**
 * @brief Calculates the length of the to be cleaned input.
 * @param temp The input list.
 * @param env The environment list.
*/
int	new_length(t_input_list *temp, t_env_list *env)
{
	int		i;
	char	quote;
	int		length;

	i = 0;
	quote = 'a';
	length = 0;
	while (temp->input[i] != '\0')
	{
		if (ft_strchr("'\"", temp->input[i]) != NULL)
			length += cleaner_quote_found(temp->input[i], &quote, temp);
		else if (temp->input[i] != '$')
			length++;
		else
			length += found_dollar(temp, &i, quote, env);
		if (temp->input[i] != '\0')
			i++;
	}
	return (length);
}
