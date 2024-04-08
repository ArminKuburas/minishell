/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:32:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/08 15:26:57 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_up_data(t_parse_data *parse_data, char **split_input)
{
	int	i;
	int	process_number;

	i = 0;
	process_number = 0;
	printf("Inside set up data before first if statement\n");
	if (split_input[0][0] != '>' && split_input[0][0] != '<')
	{
		printf("Inside set up data while loop 1\n");
		parse_data->child_data[process_number].command = split_input[0];
		i++;
		while (split_input[i] != NULL && split_input[i][0] != '|')
			i++;
	}
	while (process_number < parse_data->processes)
	{
		printf("Inside set up data before first if statement\n");
		while (split_input[i] != NULL && split_input[i][0] != '|')
		{
			if (split_input[i][0] != '>' && split_input[i][0] != '<' &&
				split_input[i - 1][0] != '>' && split_input[i - 1][0] != '<')
			{
				printf("Inside set up data while loop 2\n");
				parse_data->child_data[process_number].command = split_input[i];
				while (split_input[i] != NULL && split_input[i][0] != '|')
					i++;
			}
			if (split_input[i] != NULL)
				i++;
		}
		if (split_input[i] != NULL)
			i++;
		process_number++;
	}
	process_number = 0;
	while (process_number < parse_data->processes)
	{
		printf("inside print loop\n");
		printf("Command %d: %s\n", process_number + 1, parse_data->child_data[process_number].command);
		process_number++;
	}
	return (NO_ERROR);
}

int	parse_split_input(t_shelldata *data)
{
	int				i;
	int				error;
	t_parse_data	parse_data;

	i = 0;
	parse_data.processes = 1;
	while (data->split_input[i] != NULL)
	{
		if (data->split_input[i][0] == '|')
			parse_data.processes++;
		i++;
	}
	printf("the amount of processes we have: %d\n", parse_data.processes);
	parse_data.child_data
		= ft_calloc(parse_data.processes + 1, sizeof(t_child_data));
	if (parse_data.child_data == NULL)
		return (NO_MEMORY);
	error = set_up_data(&parse_data, data->split_input);
	if (error != NO_ERROR)
		return (FAILURE);
	return (SUCCESS);
}
