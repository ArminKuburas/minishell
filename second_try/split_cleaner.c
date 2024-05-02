/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/02 05:57:29 by akuburas         ###   ########.fr       */
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

void	set_up_string_data(t_new_string_data *data, t_input_list *temp,
	t_shelldata *shell_data, char *new_string)
{
	data->i = 0;
	data->j = 0;
	data->quote = 'a';
	data->temp = temp;
	data->env = env;
	data->new_string = new_string;
	data->shell_data = shell_data;
}

void	handle_dollar_sign(t_new_string_data *data)
{
	if (data->quote == 'a')
		potential_split_create(data);
	else
		copy_dollar(data);
}

int	create_new_string(t_input_list *temp, t_shelldata *shell_data, char *n_str)
{
	t_new_string_data	data;

	set_up_string_data(&data, temp, shell_data, n_str);
	while (data.temp->input[data.j] != '\0')
	{
		if (ft_strchr("'\"", data.temp->input[data.j]) != NULL)
			new_str_quote_found(&data, &data.temp->input[data.j]);
		else if (data.temp->input[data.j] != '$' || data.quote == '\'')
		{
			data.new_string[data.i] = data.temp->input[data.j];
			data.i++;
		}
		else
			handle_dollar_sign(&data);
		data.j++;
	}
	data.temp->old_input = temp->input;
	data.temp->input = data.new_string;
	return (SUCCESS);
}

void	clean_up_split(t_shelldata *data, t_input_list *temp)
{
	size_t	length;
	char	*str;

	str = (char *)ft_calloc(length + 1, sizeof(char));
	if (str == NULL)
		split_memory_failed(data);
	if (create_new_string(temp, data, str) != SUCCESS)
	{
		clear_input(data->input_list, NO_MEMORY);
		return (NO_MEMORY);
	}
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
		if (temp->needs_cleaning != 0)
			clean_up_split(data, temp);
		temp = temp->next;
		while (temp != NULL && temp->word_split == WORD_SPLIT)
			temp = temp->next;
	}
	return (SUCCESS);
}
