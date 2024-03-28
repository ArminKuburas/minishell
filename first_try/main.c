/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/28 13:27:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char *input2;
	//t_shelldata	data;

	if (argc < 1)
		printf("wtf\n");
	if (!argv[0])
		printf("wtf2\n");
	if (!env[0])
		printf("wtf3\n");
	while (1)
	{
		input = readline("shitshell-0.02:");
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
			printf("You inputed: %s\n", input);
			input2 = readline("oh shit 2:");
			//data.split_input = mini_split(input);
			add_history(input);
		}
		free(input);
	}
	rl_clear_history();
}
