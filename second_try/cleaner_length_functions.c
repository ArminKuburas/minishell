/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_length_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:06:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/10 21:19:34 by akuburas         ###   ########.fr       */
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
		while (ft_strchr(" \t$'\"", temp->input[(*i)]) == NULL)
			(*i)++;
		length += length_find_env(env, temp->input[start], (*i) - start);
		(*i)--;
		return (length);
	}
	return (1);
}

int	quote_found(char input, char *quote)
{
	if (*quote == 'a')
		*quote = input;
	else if (*quote == input)
		*quote = 'a';
	else
		return (1);
	return (0);
}

int	new_length(t_input_list *temp, t_env_list *env)
{
	int		i;
	char	quote;
	int		length;

	i = 0;
	quote = 'a';
	length = 0;
	while (temp->input != '\0')
	{
		if (ft_strchr("'\"", temp->input[i]) != NULL)
			length += quote_found(temp->input[i], &quote);
		else if (temp->input[i] != '$')
			length++;
		else
			length += found_dollar(temp->input, &i, quote, env);
		if (temp->input[i] != '\0')
			i++;
	}
	return (length);
}
