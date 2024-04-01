/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:32:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/01 16:08:57 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*Update this note later. First we have to understand what we are parsing and what for.
First of all we need to make sure we seperate the data properly. Sometimes the data spliting might give us a wrong string
What I mean by this is for example if an input looks like this: ls -l|echo hello world
We need to recognize that we should split up -l|echo into -l and echo to be properly used by execve.
Secondly we need to recognize the special characters we see and also properly order things as needed.
For example figuring out how to handle things like: ls -l > example1 >> example2 (where does the data go?)
I have a few ideas here but its very understandable why the parser is so important. We need to have a struct that can handle all this various data
We will also need a function that properly distrubutes the data within such a structure
Lastly of course we will need to properly handle any errors beforehand as well since I would rather handle errors before making child processes*/
void	parse_split_input(t_shelldata *data)
{
	int	i;
	int	amount_of_commands;

	i = 0;
	while (data->split_input[i] != NULL)
	{
		if (data->split_input[i][0] != '\'' && data->split_input[i][0] != '"')
			//try to find the | character and increment the amount of commands if you do find it.
		i++;
	}
}
