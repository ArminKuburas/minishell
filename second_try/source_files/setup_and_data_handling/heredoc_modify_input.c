/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_modify_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:03:54 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 15:56:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file heredoc_modify_input.c
 * @brief Functions for modifying input for heredoc.
*/

/**
 * @brief Finds the length of the environment variable value.
 * @param input The input to be used.
 * @param env_list The environment list to be used.
 * @param original_i The original index of the input.
 * @return The length of the environment variable value.
*/
int	found_dollar_sign(char *input, t_env_list *env_list, int *original_i)
{
	int			i;
	t_env_list	*temp;

	temp = env_list;
	i = 0;
	while (input[i] != '\0' && ft_strchr(" \t\n$?", input[i]) == NULL)
		i++;
	if (i == 0 && input[i] == '?')
		i++;
	*original_i += i;
	while (temp != NULL)
	{
		if ((size_t)i == ft_strlen(temp->env_var_name))
		{
			if (ft_strncmp(input, temp->env_var_name, i) == 0)
				return (ft_strlen(temp->env_var_value));
		}
		temp = temp->next;
	}
	return (0);
}

/**
 * @brief Finds the length of the modified input.
 * @param input The input to be used.
 * @param env_list The environment list to be used.
 * @return The length of the modified input.
*/
int	modified_length(char *input, t_env_list *env_list)
{
	int		i;
	int		length;

	i = 0;
	length = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			i++;
			length += found_dollar_sign(&input[i], env_list, &i);
			i--;
		}
		else
			length++;
		i++;
	}
	return (length);
}

/**
 * @brief sets up the new input dollar 
 * @param input The input to be used.
 * @param new_input The new input to be used.
 * @param env_list The environment list to be used.
 * @param j The index of the new input.
 * @return The length of the environment variable name.
*/
int	new_input_dollar(char *input, char *new_input, t_env_list *env_list, int *j)
{
	int			i;
	t_env_list	*temp;

	i = 0;
	temp = env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(input, temp->env_var_name,
				ft_strlen(temp->env_var_name)) == 0)
		{
			ft_strlcpy(&new_input[*j], temp->env_var_value,
				ft_strlen(temp->env_var_value) + 1);
			*j += ft_strlen(temp->env_var_value);
			i += ft_strlen(temp->env_var_name) + 1;
			return (i);
		}
		temp = temp->next;
	}
	if (ft_strchr(" \t\n$", input[i]) != NULL)
		return (no_env_found(new_input, j));
	while (input[i] != '\0' && ft_strchr(" \t\n$", input[i]) == NULL)
		i++;
	return (i + 1);
}

/**
 * @brief Sets up the new input.
 * @param input The input to be used.
 * @param new_input The new input to be used.
 * @param env_list The environment list to be used.
*/
void	set_up_new_input(char *input, char *new_input, t_env_list *env_list)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			i += new_input_dollar(&input[i + 1], new_input, env_list, &j);
		else
			new_input[j++] = input[i++];
	}
}

/**
 * @brief Modifies the input for heredoc.
 * @param input The input to be used.
 * @param env_list The environment list to be used.
 * @return The modified input.
*/
char	*modify_input(char *input, t_env_list *env_list)
{
	char	*new_input;

	new_input = ft_calloc(modified_length(input, env_list) + 1, sizeof(char));
	if (new_input == NULL)
		return (NULL);
	set_up_new_input(input, new_input, env_list);
	return (new_input);
}
