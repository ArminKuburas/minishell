/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:44:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/19 04:19:14 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	duplicate_quote(t_split_data *data, t_shelldata *shell_data)
{
	char	*temp;
	int		i;

	printf("Inside duplicate quote\n");
	data->quote = data->input[data->i];
	temp = ft_strchr(&data->input[data->i + 1], data->quote);
	if (ft_strchr("<>| ", temp[1]) == NULL)
	{
		printf("inside first if statement\n");
		i = 1;
		while (ft_strchr("<>| ", temp[i]) == NULL)
		{
			if (temp[i] == '\'' || temp[i] == '"')
			{
				printf("Inside if statement of duplicaate quote\n");
				data->quote = temp[i];
				printf("before if statement loop. i = %d\n", i);
				while (temp[i] && temp[i] != data->quote)
					i++;
				data->quote = '\0';
				printf("After if statement loop. i = %d\n", i);
			}
			if (temp[i] != '\0')
				i++;
		}
		if (create_input(&data->input[data->i], temp - data->input
				- data->i + i + 1, shell_data->input_list) != SUCCESS)
			return (FAILURE);
	}
	else
	{
		printf("Inside else statement of duplicate quote\n");
		if (create_input(&data->input[data->i], temp - data->input
				- data->i + 1, shell_data->input_list) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	old_duplicate_special_character(t_split_data *data, t_input_list *input_list)
{
	if (ft_strchr("><", data->input[data->i + 1])
		!= NULL && data->input[data->i] == data->input[data->i + 1])
	{
		if (ft_strchr("><|", data->input[data->i + 2]) != NULL)
		{
			ft_putstr_fd("Error: Syntax error\n", 2);
			return (FAILURE);
		}
		else
			if (create_input(data->input + data->i, 2, input_list) != SUCCESS)
				return (FAILURE);
	}
	else
		if (create_input(data->input + data->i, 1, input_list) != SUCCESS)
			return (FAILURE);
	return (SUCCESS);
}

int	old_duplicate_input(t_split_data *data, t_shelldata *shell_data)
{
	int	i;

	i = data->i;
	printf("Inside duplicate input\n");
	if (ft_strchr("><|", data->input[data->i]) != NULL)
		return (old_duplicate_special_character(data, shell_data->input_list));
	while (data->input[data->i] != '\0' && data->input[data->i] != ' ')
	{
		if (data->input[data->i] == '\'' || data->input[data->i] == '"')
			if (parser_quote_found(data) != SUCCESS)
				return (FAILURE);
		if (ft_strchr("><|", data->input[data->i]) != NULL)
			break ;
		if (data->input[data->i] != '\0')
			data->i++;
	}
	if (create_input(data->input + i, data->i - i, shell_data->input_list)
		!= SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	create_strings(t_split_data *data, t_shelldata *shell_data)
{
	int	error;

	error = SUCCESS;
	printf("Inside create_strings\n");
	while (data->word_count > 0)
	{
		while (data->input[data->i] == ' ')
			(data->i)++;
		if (data->input[data->i] == '\0')
			break ;
		if (data->input[data->i] == '"' || data->input[data->i] == '\'')
			error = duplicate_quote(data, shell_data);
		else
			error = old_duplicate_input(data, shell_data);
		if (error != SUCCESS)
			return (FAILURE);
		data->i += strlen_last_input(shell_data->input_list);
	}
	return (SUCCESS);
}

void	set_up_split_data(t_split_data *split_data, char *input)
{
	split_data->i = 0;
	split_data->len = ft_strlen(input);
	split_data->word_count = 0;
	split_data->quote = '\0';
	split_data->input = input;
	split_data->node_one = NULL;
}

/* This function is used to split the given input into seperate lines.
These will later be filtered into the parser.
In addition it returns an error value if something fails.*/
int	mini_split(char *input, t_shelldata *shell_data)
{
	t_split_data	split_data;

	set_up_split_data(&split_data, input);
	if (count_words(&split_data) != SUCCESS)
		return (FAILURE);
	printf("after count_words\n");
	printf("word_count: %d\n", split_data.word_count);
	shell_data->input_list = (t_input_list *)ft_calloc(1, sizeof(t_input_list));
	if (shell_data->input_list == NULL)
		return (NO_MEMORY);
	printf("after allocating for input list\n");
	split_data.i = 0;
	split_data.quote = '\0';
	if (create_strings(&split_data, shell_data) != SUCCESS)
		return (FAILURE);
	printf("after creating strings\n");
	input_type_assigner(shell_data->input_list);
	t_input_list	*temp;
	int				i;
	temp = shell_data->input_list;
	i = 0;
	printf("word_count: %d\n", split_data.word_count);
	printf("Before split_cleaner\n");
	while (temp != NULL)
	{
		printf("input split %d: %s\n", i + 1, temp->input);
		printf("input type %d: %d\n", i + 1, temp->type);
		i++;
		temp = temp->next;
	}
	if (split_cleaner(shell_data) != SUCCESS)
		return (FAILURE);
	printf("--------------------\n");
	printf("After split_cleaner\n");
	return (SUCCESS);
}
