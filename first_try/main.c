/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/04 18:45:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	duplicate_env(char **env, t_shelldata *data)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env_variables = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!data->env_variables)
		return (NO_MEMORY);
	i = 0;
	while (env[i])
	{
		data->env_variables[i] = ft_strdup(env[i]);
		if (!data->env_variables[i])
		{
			free_double_array(&data->env_variables);
			return (NO_MEMORY);
		}
		i++;
	}
	data->env_variables[i] = NULL;
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_shelldata	data;
	int			error;
	int			i;

	if (argc < 1)
		printf("wtf\n");
	if (!argv[0])
		printf("wtf2\n");
	if (env)
	{
		error = duplicate_env(env, &data);
		if (error == NO_MEMORY)
		{
			printf("Error: No memory\n");
			return (FAILURE);
		}
	}
	while (1)
	{
		input = readline("bananashell-0.07:");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				printf("exit\n");
				free(input);
				break ;
			}
			error = mini_split(input, &data);
			if (error == SUCCESS)
			{
				i = 0;
				while (data.split_input[i])
				{
					printf("split_input[%d] = %s\n", i, data.split_input[i]);
					i++;
				}
				printf("--------------------\n");
				parse_split_input(&data);
				free_double_array(&data.split_input);
			}
			add_history(input);
		}
		free(input);
	}
	rl_clear_history();
}
