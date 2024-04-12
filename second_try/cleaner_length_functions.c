/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_length_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:06:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/11 18:45:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	length_find_env(t_env_list *env, char *str, int len)
{
	int			length;
	t_env_list	*temp;

	temp = env;
	length = 0;
	while (temp != NULL)
	{
		if (ft_strlen(temp->env_var_name) != len)
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
		if (quote == 'a')
			temp->word_split = POTENTIAL_SPLIT;
		return (length);
	}
	return (1);
}

int	cleaner_quote_found(char input, char *quote)
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
			length += cleaner_quote_found(temp->input[i], &quote);
		else if (temp->input[i] != '$')
			length++;
		else
			length += found_dollar(temp, &i, quote, env);
		if (temp->input[i] != '\0')
			i++;
	}
	return (length);
}
