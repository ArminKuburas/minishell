/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:41:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/19 12:05:33 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_found(char *quote, char c)
{
	if (*quote == '\0')
		*quote = c;
	else if (*quote == c)
		*quote = '\0';
}

int	duplicate_input(char *input, t_input_list *input_list, int *i)
{
	int		j;
	char	quote;

	quote = '\0';
	j = 0;
	while (input[j])
	{
		if (input[j] == '\'' || input[j] == '"')
			quote_found(&quote, input[j]);
		if (quote == '\0' && ft_strchr("<>| \t", input[j]))
			break ;
		j++;
	}
	if (quote != '\0')
	{
		ft_putstr_fd("Error: No closing quote found\n", 2);
		return (NO_QUOTE);
	}
	if (create_input(input, j, input_list) != SUCCESS)
		return (FAILURE);
	*i += j - 1;
	return (SUCCESS);
}

int	duplicate_special_character(char *input, t_input_list *input_list, int *i)
{
	if (ft_strchr("><", input[1]) != NULL && input[0] == input[1])
	{
		if (ft_strchr("><|", input[2]) != NULL)
		{
			ft_putstr_fd("Error: Syntax error\n", 2);
			return (FAILURE);
		}
		if (create_input(input, 2, input_list) != SUCCESS)
			return (FAILURE);
	}
	else
	{
		if (ft_strchr("><|", input[1]) != NULL)
		{
			ft_putstr_fd("Error: Syntax error\n", 2);
			return (FAILURE);
		}
		if (create_input(input, 1, input_list) != SUCCESS)
			return (FAILURE);
	}
	*i += strlen_last_input(input_list) - 1;
	return (SUCCESS);
}

int	new_mini_split(t_shelldata *data)
{
	int		i;

	i = 0;
	data->input_list = ft_calloc(1, sizeof(t_input_list));
	if (data->input_list == NULL)
		return (NO_MEMORY);
	while (data->input[i])
	{
		while (data->input[i] == ' ' || data->input[i] == '\t')
			i++;
		if (ft_strchr("><|", data->input[i]) != NULL)
		{
			if (duplicate_special_character(&data->input[i],
					data->input_list, &i) != SUCCESS)
				return (clear_input(data->input_list, FAILURE));
		}
		else
			if (duplicate_input(&data->input[i], data->input_list,
					&i) != SUCCESS)
				return (clear_input(data->input_list, FAILURE));
		if (data->input[i] != '\0')
			i++;
	}
	t_input_list *temp = data->input_list;
	int j = 0;
	printf("--------------------\n");
	printf("input before cleaning\n");
	while (temp != NULL)
	{
		printf("input[%d] = %s\n", j, temp->input);
		temp = temp->next;
	}
	input_type_assigner(data->input_list);
	temp = data->input_list;
	j = 0;
	printf("--------------------\n");
	printf("after input type assigner\n");
	while (temp != NULL)
	{
		printf("input[%d] type = %d\n", j, temp->type);
		j++;
		temp = temp->next;
	}
	if (split_cleaner(data) != SUCCESS)
		return (FAILURE);
	printf("--------------------\n");
	printf("input after cleaning\n");
	return (SUCCESS);
}
