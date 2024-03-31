/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 12:21:08 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/31 12:24:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Included because of the use of NULL*/
#include "minishell.h"

/*Function to free a double array of strings
Since we are modifying the array itself we need a pointer to it*/
void	free_double_array(char ***array)
{
	int	i;

	i = 0;
	if (!*array)
		return ;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}