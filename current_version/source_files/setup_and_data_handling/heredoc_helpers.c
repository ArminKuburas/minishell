/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:37:51 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/26 14:38:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file heredoc_helpers.c
 * @brief Helper functions for heredoc.
*/

/**
 * @brief Helper function for the cleaner.
 * @param input The input line.
 * @param cleaned_input The cleaned input line.
 * @return void
*/
void	cleaner_helper(char *input, char *cleaned_input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (ft_strchr("'\"", input[i]) == NULL)
		{
			cleaned_input[j] = input[i];
			j++;
		}
		i++;
	}
}
