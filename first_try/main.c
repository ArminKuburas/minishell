/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/01 18:10:30 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	signal_handler(int signal)
{
	if (signal == CTRL_C)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// exit code = 130, A job with exit code 130 was terminated with signal 2 (SIGINT on most systems, 130-128 = 2)
	}
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
	if (!env[0])
		printf("wtf3\n");
	while (1)
	{
		signal(CTRL_C, signal_handler);
		input = readline("bananashell-0.05:");
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
				//parse_split_input(&data);
				free_double_array(&data.split_input);
			}
			add_history(input);
		}
		free(input);
	}
	rl_clear_history();
}
