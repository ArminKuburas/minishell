/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:44:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/10 15:40:22 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	duplicate_quote(char *input, t_shelldata *data, int j)
{
	char	quote;
	int		i;
	char	*temp;

	quote = input[j];

	temp = ft_strchr(input + j + 1, quote);
	if (ft_strchr("<>| ", temp[1]) == NULL)
	{
		i = 1;
		while (ft_strchr("<>| ", temp[i]) == NULL)
			i++;
		if (create_input(input + j, temp - input - j + i + 1, data->input_list) != SUCCESS)
			return (FAILURE);
	}
	else
		if (create_input(input + j, temp - input - j + 1, data->input_list) != SUCCESS)
			return (FAILURE);
	return (SUCCESS);
}


int	duplicate_input(char *input, t_shelldata *data, int j)
{
	int	i;

	i = j;
	if (ft_strchr("><|", input[j]) != NULL)
	{
		if (ft_strchr("><", input[j + 1]) != NULL && input[j] == input[j + 1])
		{
			if (ft_strchr("><|", input[j + 2]) != NULL)
			{
				ft_putstr_fd("Error: Syntax error\n", 2);
				return (FAILURE);
			}
			else
				if (create_input(input + j, 2, data->input_list) != SUCCESS)
					return (FAILURE);
		}
		else
			if (create_input(input + j, 1, data->input_list) != SUCCESS)
				return (FAILURE);
		return (SUCCESS);
	}
	while (input[j] != ' ' && input[j] != '\0')
	{
		if (ft_strchr("><|", input[j]) != NULL)
			break ;
		j++;
	}
	if (create_input(input + i, j - i, data->input_list) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);}

int	strlen_last_input(t_input_list *input_list)
{
	t_input_list	*temp;
	int				i;

	temp = input_list;
	i = 0;
	while (temp->next != NULL)
		temp = temp->next;
	while (temp->input[i] != '\0')
		i++;
	return (i);
}

int	create_strings(char *input, t_shelldata *data, int word_count)
{
	int	i;
	int	amount;
	int	error;

	i = 0;
	amount = 0;
	error = SUCCESS;
	while (amount < word_count)
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		if (input[i] == '"' || input[i] == '\'')
			error = duplicate_quote(input, data, i);
		else
			error = duplicate_input(input, data, i);
		if (error != SUCCESS)
			return (FAILURE);
		i += strlen_last_input(data->input_list);
	}
	return (SUCCESS);
}

/* This function is used to split the given input into seperate lines.
These will later be filtered into the parser.
In addition it returns an error value if something fails.*/
int	mini_split(char *input, t_shelldata *data)
{
	int		word_count;

	word_count = 0;
	if (count_words(input, &word_count) != SUCCESS)
		return (FAILURE);
	data->input_list = (t_input_list *)ft_calloc(1, sizeof(t_input_list));
	if (data->input_list == NULL)
		return (NO_MEMORY);
	if (create_strings(input, data, word_count) != SUCCESS)
		return (FAILURE);
	t_input_list	*temp;
	int				i;
	temp = data->input_list;
	i = 0;
	printf("word_count: %d\n", word_count);
	printf("Before split_cleaner\n");
	while (temp != NULL)
	{
		printf("input split %d: %s\n", i + 1, temp->input);
		i++;
		temp = temp->next;
	}
	//if (split_cleaner(data) != SUCCESS)
	//	return (FAILURE);
	//printf("--------------------\n");
	//printf("After split_cleaner\n");
	return (SUCCESS);
}
