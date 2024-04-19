/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_substrings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:57:27 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/16 04:00:11 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_substrings(char ***arr_str)
{
	int	i;

	i = 0;
	while ((*arr_str)[i] != NULL)
	{
		free((*arr_str)[i]);
		(*arr_str)[i] = NULL;
		i++;
	}
	if ((*arr_str) != NULL)
	{
		free((*arr_str));
		(*arr_str) = NULL;
	}
}
