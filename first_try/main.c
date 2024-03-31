/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/31 19:47:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
