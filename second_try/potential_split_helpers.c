/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_split_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 06:19:36 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 10:57:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function just establishes the new data.
Given parameters are the old link, the new link and the input*/
static void	set_up_link(t_input_list *o_link, t_input_list *n_link, char *input)
{
	n_link->next = o_link->next;
	o_link->next = n_link;
	n_link->input = input;
	n_link->prev = o_link;
	n_link->word_split = WORD_SPLIT;
	n_link->type = COMMAND_ARGUMENT;
}

static void	initialize_first_link(t_new_string_data *data, char **strings)
{
	int	j;

	j = 0;
	while (strings[0][j] != '\0')
	{
		data->new_string[data->i] = strings[0][j];
		data->i++;
		j++;
	}
	data->temp->word_split = WORD_SPLIT;
	data->temp->old_input = data->temp->input;
	data->temp->input = ft_strdup(data->new_string);
	if (data->temp->input == NULL)
	{
		ft_free_substrings(&strings);
		split_memory_failed(data->shell_data);
	}
	free(strings[0]);
}

static void	create_middle_links(t_new_string_data *data, char **strings)
{
	t_input_list	*new_link;
	int				i;

	i = 1;
	while (strings[i] != NULL)
	{
		new_link = ft_calloc(1, sizeof(t_input_list));
		if (new_link == NULL)
		{
			ft_free_substrings(&strings);
			split_memory_failed(data->shell_data);
		}
		set_up_link(data->temp, new_link, strings[i]);
		i++;
		new_link = NULL;
		data->temp = data->temp->next;
	}
}

static void	finish_last_link(t_new_string_data *data, char **strings)
{
	int				j;
	t_input_list	*old_link;

	j = 0;
	data->i = 0;
	while (data->temp->input[j] != '\0')
	{
		data->new_string[data->i] = data->temp->input[j];
		j++;
		data->i++;
	}
	free(data->temp->input);
	data->temp->input = NULL;
	old_link = data->temp;
	while (old_link->old_input == NULL)
		old_link = old_link->prev;
	data->temp->input = ft_strdup(old_link->old_input);
	data->j--;
	if (data->temp->input == NULL)
	{
		ft_free_substrings(&strings);
		split_memory_failed(data->shell_data);
	}
}

void	split_env(t_new_string_data *data, t_env_list	*temp_env)
{
	char			**strings;

	strings = ft_split(temp_env->env_var_value, ' ');
	if (strings == NULL)
		split_memory_failed(data->shell_data);
	initialize_first_link(data, strings);
	create_middle_links(data, strings);
	ft_memset(data->new_string, 0, ft_strlen(data->new_string));
	finish_last_link(data, strings);
	free(strings);
}
