/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:24:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/05 21:48:21 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_input_list(t_input_list *input_list, t_input_list *new_node)
{
	t_input_list	*temp;

	temp = input_list;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = NULL;
	new_node->prev = temp;
}

int	clear_input(t_input_list *input_list, int error)
{
	t_input_list	*temp;

	printf("clear_input is being called\n");
	while (input_list != NULL)
	{
		printf("input_list->input: %s\n", input_list->input);
		if (input_list->old_input != NULL)
			printf("input_list->old_input: %s\n", input_list->old_input);
		temp = input_list->next;
		if (input_list->input != NULL)
			free(input_list->input);
		printf("input_list->input freed\n");
		if (input_list->old_input != NULL)
			free(input_list->old_input);
		printf("input_list->old_input freed\n");
		input_list->input = NULL;
		input_list->old_input = NULL;
		free(input_list);
		input_list = temp;
	}
	if (error == NO_MEMORY)
		ft_putstr_fd("Error: No memory\n", 2);
	return (error);
}

int	create_input(char *input, int len, t_input_list *input_list)
{
	t_input_list	*new_node;

	if (input_list->input == NULL)
	{
		input_list->input = ft_strndup(input, len);
		if (input_list->input == NULL)
			return (NO_MEMORY);
	}
	else
	{
		new_node = (t_input_list *)ft_calloc(1, sizeof(t_input_list));
		if (new_node == NULL)
			return (NO_MEMORY);
		add_input_list(input_list, new_node);
		new_node->input = ft_strndup(input, len);
		if (new_node->input == NULL)
			return (NO_MEMORY);
	}
	return (SUCCESS);
}

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
