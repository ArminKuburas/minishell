/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/14 14:34:00 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_str_quote_found(t_new_string_data *data, char *temp)
{
	if (data->quote == 'a')
		data->quote = *temp;
	else if (data->quote == *temp)
		data->quote = 'a';
	else
	{
		data->new_string[data->i] = *temp;
		data->i++;
	}
}

int	new_string_last_check(t_input_list *temp)
{
	if (temp->word_split == FAILURE)
		return (NO_MEMORY);
	return (SUCCESS);
}

void	set_up_string_data(t_new_string_data *data, t_input_list *temp,
	t_env_list *env, char *new_string)
{
	data->i = 0;
	data->j = 0;
	data->quote = 'a';
	data->temp = temp;
	data->env = env;
	data->new_string = new_string;
}

void	handle_dollar_sign(t_new_string_data *data)
{
	if (data->quote == 'a')
		potential_split_create(data);
	else
		copy_dollar(data);
}

int	create_new_string(t_input_list *temp, t_env_list *env, char *new_string)
{
	t_new_string_data	data;

	set_up_string_data(&data, temp, env, new_string);
	while (temp->input[data.j] != '\0')
	{
		if (ft_strchr("'\"", temp->input[data.j]) != NULL)
			new_str_quote_found(&data, &temp->input[data.j]);
		else if (temp->input[data.j] != '$' || data.quote == '\'')
		{
			printf("Inside create_new_string loop\n");
			printf("Inside if statement in create_new_string loop\n");
			new_string[data.i] = temp->input[data.j];
			printf("data.i: %d\n", data.i);
			data.i++;
		}
		else
			handle_dollar_sign(&data);
		if (new_string_last_check(temp) == NO_MEMORY)
			return (NO_MEMORY);
		printf("Inside create_new_string loop\n");
		printf("data.i: %d\n", data.i);
		printf("data.j: %d\n", data.j);
		printf("data.quote: %c\n", data.quote);
		printf("data.new_string: %s\n", data.new_string);
		printf("temp->input[data.j]: %c\n", temp->input[data.j]);
		data.j++;
	}
	temp->old_input = temp->input;
	temp->input = new_string;
	return (SUCCESS);
}

int	split_cleaner(t_shelldata *data)
{
	size_t			length;
	t_input_list	*temp;
	char			*str;

	temp = data->input_list;
	while (temp != NULL)
	{
		length = new_length(temp, data->env_list);
		printf("Length: %zu\n", length);
		printf("Original length of input: %zu\n", ft_strlen(temp->input));
		if (temp->needs_cleaning != 0)
		{
			str = (char *)ft_calloc(length + 1, sizeof(char));
			if (str == NULL)
			{
				clear_input(data->input_list, NO_MEMORY);
				return (NO_MEMORY);
			}
			if (create_new_string(temp, data->env_list, str) != SUCCESS)
			{
				clear_input(data->input_list, NO_MEMORY);
				return (NO_MEMORY);
			}
		}
		temp = temp->next;
		while (temp != NULL && temp->word_split == WORD_SPLIT)
			temp = temp->next;
	}
	return (SUCCESS);
}
