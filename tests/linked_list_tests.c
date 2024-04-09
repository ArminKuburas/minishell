/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:04:14 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/09 04:00:29 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

void	make_list(t_list *list, int size)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	list->next = new;
	new->next = NULL;
	new->content = size;
	new->prev = list;
}

int	main(void)
{
	t_list	*list;
	t_list	*start;
	int		size;

	list = malloc(sizeof(t_list));
	list->next = NULL;
	list->prev = NULL;
	list->content = 0;
	start = list;
	size = 5;
	while (size >= 0)
	{
		make_list(list, size);
		printf("content: %d\n", list->content);
		size--;
		printf("size: %d\n", size);
		list = list->next;
	}
	list = start;
	while (list->next != NULL)
	{
		printf("content: %d\n", list->content);
		list = list->next;
		free(list->prev);
	}
	return (0);
}
