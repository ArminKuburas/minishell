/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/04 08:55:17 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*The goal of this function is to remove certain quotes and also expanding dollar signs inside "" and on their own but not when inside 'single quotes'
Also not inside double quotes if said quotes are inside single quotes. We also shouldnt remove quotes within quotes from the strings
So for example ec"ho" should become echo. $EXAMPLE should try to find EXAMPLE inside the env and remove $EXAMPLE from the string and add in what it finds in the env. If it cant find anything it just removes the $EXAMPLE
We won't handle $$ like bash does. Instead it will try to find $ inside the env, probably wont find it and just remove the $$. if a $ is on its own like "hello $ goodbye" it should leave the dollar sign alone.*/

int	split_cleaner(t_shelldata *data)
{
	int		i;
	int		j;
	int		single_quote_switch;

	single_quote_switch = 0;
	i = 0;
	//first we want to know how large the new string has to be if its the same size as the old one then it means no changes have to happen
	while (data->split_input[i] != NULL)
	{
		j = 0;
		while (data->split_input[i][j] != '\0')
		{
			if (data->split_input[i][j] == '\'')
			{
				if (single_quote_switch == 0)
					single_quote_switch = 1;
				else
					single_quote_switch = 0;
			}
		}
		i++;
	}
	return (SUCCESS);
}
