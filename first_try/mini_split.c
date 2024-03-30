/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:44:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/30 14:12:10 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This function is used to split the given input into seperate lines.
These will later be filtered into the parser.
In addition it should also prompt the user if it finds an unfinished quote*/
int	mini_split(char *input, t_shelldata *data)
{
	int		word_count;
	int		i;
	int		len;
	char	quote;
	int		j;

	len = ft_strlen(input);
	i = 0;
	j = 0;
	word_count = 0;
	while (i < len)
	{
		while (i < len && input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		word_count ++;
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			while (i < len && input[i] != quote)
				i++;
			if (input[i] != quote)
			{
				printf("Unfinished quote\n");
				return (NO_QUOTE);
			}
			if (i < len)
				i++;
		}
		else
		{
			while (i < len && input[i] != ' ')
				i++;
		}
	}
	data->split_input = (char **)malloc((word_count + 1) * sizeof(char *));
	if (data->split_input == NULL)
		return (NO_MEMORY);
	while (j <= word_count)
	{
		data->split_input
	}
}
