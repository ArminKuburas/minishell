/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/10 17:17:19 by tvalimak         ###   ########.fr       */
=======
/*   Updated: 2024/04/08 15:56:32 by akuburas         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// when in heredoc and CTR+C the ^C will not display
// when in bash and you have inputted cat for example, then you CTRL+C the ^C will display
// without prompt.
// When terminal is opened for the first time and you do CTRL+C in bash, the ^C is shown for once,
// need to figure out why.
// CTRL + \ = SIGQUIT

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
		parent_signals();
		input = readline("bananashell-0.09:");
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
