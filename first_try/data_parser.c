/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:32:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/02 16:06:02 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	set_up_data(t_parse_data *parse_data)
{
	int	i;
	int	save_position;

	i = 0;
	save_position = 0;
	while (parse_data->processes > 0)
	{
		while()
	}
	while
}

/*Update this note later. First we have to understand what we are parsing and what for.
First of all we need to make sure we seperate the data properly. Sometimes the data spliting might give us a wrong string
What I mean by this is for example if an input looks like this: ls -l|echo hello world
We need to recognize that we should split up -l|echo into -l and echo to be properly used by execve.
Secondly we need to recognize the special characters we see and also properly order things as needed.
For example figuring out how to handle things like: ls -l > example1 >> example2 (where does the data go?)
I have a few ideas here but its very understandable why the parser is so important. We need to have a struct that can handle all this various data
We will also need a function that properly distrubutes the data within such a structure
Lastly of course we will need to properly handle any errors beforehand as well since I would rather handle errors before making child processes*/
int	parse_split_input(t_shelldata *data)
{
	int				i;
	int				error;
	t_parse_data	parse_data;

	i = 0;
	parse_data.processes = 1;
	while (data->split_input[i] != NULL)
	{
		if (data->split_input[i][0] != '\'' && data->split_input[i][0] != '"')
		{
			if (data->split_input[i][0] == '|')
				parse_data.processes++;
		}
		i++;
	}
	printf("Inside the parser. This is how many commands there are: %d\n", parse_data.processes);
	parse_data.child_data = malloc((parse_data.processes) * sizeof(t_child_data));
	if (parse_data.child_data == NULL)
		return (NO_MEMORY);
	error = set_up_data(&parse_data);
	if (error != NO_ERROR)
		return (FAILURE);
	return (SUCCESS);
}
