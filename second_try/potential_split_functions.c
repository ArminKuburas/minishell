/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potential_split_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 07:34:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/16 13:58:12 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*This function checks to see if the given $string ends with a $ character
 that is followed by nothing.
 The reason this is important is because it prevents a split from happening
 example: $TEMP="Hello World"
 If in the shell you call it like this: > $TEMP$
 it views it as one long string: Hello World$
 The space included in the string.*/
bool	check_string(t_new_string_data *data)
{
	int	start;

	start = data->j;
	printf("Inside check_string function.\n");
	printf("start = %d while input[j] = %c\n", start, data->temp->input[start]);
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		if (data->temp->input[data->j] == '$'
			&& ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) != NULL)
		{
			printf("Inside check string going to copy dollar\n");
			data->j = start;
			copy_dollar(data);
			return (1);
		}
		data->j = start;
		return (0);
	}
	printf("Inside check string function. First if statment came out false. Going to copy_dollar.\n");
	copy_dollar(data);
	return (1);
}

int	check_if_split_needed(t_env_list *temp_env)
{
	int	i;

	i = 0;
	printf("inside check if split needed\n");
	while (temp_env->env_var_value[i] != '\0')
	{
		if (ft_strchr(" \t", temp_env->env_var_value[i]) != NULL)
		{
			printf("Yes there are spaces and we must word split\n");
			return (YES);
		}
		i++;
	}
	return (NO);
}

t_env_list	*potential_find_env(t_new_string_data *data, bool *split_check)
{
	int			start;
	t_env_list	*temp_env;

	printf("Inside potential_find_env.\n");
	if (ft_strchr(" \t$'\"", data->temp->input[data->j + 1]) == NULL)
	{
		data->j++;
		start = data->j;
		while (ft_strchr(" \t$'\"", data->temp->input[data->j]) == NULL)
			data->j++;
		temp_env = try_to_find_env(data->env, &data->temp->input[start],
				data->j - start);
		if (temp_env != NULL)
		{
			printf("Inside potential find env. temp_env is not empty (env has been found) checking if it needs to be split or not\n");
			if (check_if_split_needed(temp_env) == YES)
				*split_check = 1;
			else
				data->j = start - 1;
		}
		return (temp_env);
	}
	printf("This probably should be unreachable since we check the same if statement at least like 2 times before but whatever\n");
	return (NULL);
}


/*This function just establishes the new data.
Given parameters are the old link, the new link and the input*/
void	set_up_new_link(t_input_list *o_link, t_input_list *n_link, char *input)
{
	printf("Inside set up new link\n");
	n_link->next = o_link->next;
	o_link->next = n_link;
	n_link->input = input;
	n_link->prev = o_link;
	n_link->word_split = WORD_SPLIT;
}

void	split_env(t_new_string_data *data, t_env_list	*temp_env)
{
	char			**strings;
	t_input_list	*new_link;
	int				i;
	int				j;

	printf("Inside split_env. The big galuga itself. Time to be scared.\n");
	strings = ft_split(temp_env->env_var_value, ' ');
	if (strings == NULL)
		data->temp->word_split = FAILURE;
	else
	{
		printf("After ft_split.\n");
		i = 0;
		j = 0;
		while (strings[i][j] != '\0')
		{
			data->new_string[data->i] = strings[i][j];
			data->i++;
			j++;
		}
		data->temp->word_split = WORD_SPLIT;
		data->temp->old_input = data->temp->input;
		data->temp->input = ft_strdup(data->new_string);
		if (data->temp->input == NULL)
		{
			data->temp->word_split = FAILURE;
			ft_free_substrings(&strings);
			return ;
		}
		free(strings[0]);
		i = 1;
		while (strings[i] != NULL)
		{
			printf("Inside while loop that creates new links\n");
			new_link = ft_calloc(1, sizeof(t_input_list));
			if (new_link == NULL)
			{
				data->temp->word_split = FAILURE;
				ft_free_substrings(&strings);
				return ;
			}
			set_up_new_link(data->temp, new_link, strings[i]);
			i++;
			new_link = NULL;
			data->temp = data->temp->next;
		}
		printf("After while loop that creates and sets up new links\n");
		printf("Before memset. data->new_string = %s\n", data->new_string);
		ft_memset(data->new_string, 0, ft_strlen(data->new_string));
		printf("Before while loop that copies input.\n");
		printf("input is = %s\n", data->temp->input);
		printf("prev input is = %s\n", data->temp->prev->input);
		j = 0;
		data->i = 0;
		while (data->temp->input[j] != '\0')
		{
			data->new_string[data->i] = data->temp->input[j];
			j++;
			data->i++;
		}
		printf("After while loop that supposedly copies the new string stuff. \n");
		printf("New string = %s\n", data->new_string);
		free(data->temp->input);
		data->temp->input = NULL;
		new_link = data->temp;
		printf("Before while loop that tries to find the old input\n");
		printf("This is new_link input %s\n", new_link->input);
		printf("This is new_link old input %s\n", new_link->old_input);
		while (new_link->old_input == NULL)
			new_link = new_link->prev;
		data->temp->input = ft_strdup(new_link->old_input);
		printf("Lets see what temp input is \n");
		printf("temp->input is = %s\n", data->temp->input);
		data->j--;
		if (data->temp->input == NULL)
		{
			data->temp->word_split = FAILURE;
			ft_free_substrings(&strings);
			return ;
		}
	}
}

void	potential_split_create(t_new_string_data *data)
{
	t_env_list	*temp_env;
	bool		split_check;

	printf("Inside potential_split_create\n");
	if (check_string(data) == 1)
		return ;
	split_check = 0;
	temp_env = potential_find_env(data, &split_check);
	printf("This is split_check after potential find env: %d\n", split_check);
	if (split_check == 0 && temp_env != NULL)
		copy_dollar(data);
	else if (split_check == 1)
		split_env(data, temp_env);
}
