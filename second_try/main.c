/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/13 16:59:30 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>

// when in heredoc and CTR+C the ^C will not display
// when in bash and you have inputted cat for example, then you CTRL+C the ^C will display
// without prompt.
// When terminal is opened for the first time and you do CTRL+C in bash, the ^C is shown for once,
// need to figure out why.
// CTRL + \ = SIGQUIT

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
		if (error != SUCCESS)
			return (FAILURE);
		t_env_list	*temp = data.env_list;
		while (temp != NULL)
		{
			printf("--------------------\n");
			printf("env_var = %s\n", temp->env_var);
			printf("env_var_name = %s\n", temp->env_var_name);
			printf("env_var_value = %s\n", temp->env_var_value);
			printf("--------------------\n");
			temp = temp->next;
		}
	}
	while (1)
	{
		parent_signals();
		input = readline("bananashell-0.11:");
		if (!input)
		{
			printf("exit\n");
			clear_env_list(data.env_list, SUCCESS);
			break ;
		}
		if (input)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				printf("exit\n");
				free(input);
				clear_env_list(data.env_list, SUCCESS);
				break ;
			}
			if (ft_strlen(input) == 0)
			{
				free(input);
				continue ;
			}
			error = mini_split(input, &data);
			if (error == SUCCESS)
			{
				i = 0;
				printf("This is i %d\n", i);
				//while (data.split_input[i])
				//{
				//	printf("split_input[%d] = %s\n", i, data.split_input[i]);
				//	i++;
				//}
				//printf("--------------------\n");
				//parse_split_input(&data);
				t_input_list *temp = data.input_list;
				while (temp != NULL)
				{
					if (temp->type == COMMAND)
					{
						if (ft_strcmp(temp->input, "echo") == 0)
						{
							temp = temp->next;
							my_echo(temp);
						}
						if (ft_strcmp(temp->input, "cd") == 0)
							printf("command was cd \n");
						if (ft_strcmp(temp->input, "pwd") == 0)
							printf("command was pwd \n");
						if (ft_strcmp(temp->input, "export") == 0)
							printf("command was export \n");
						// compare the input of the command with the built-in
						// names.
						// next step is to feed the input to the proper function
						// for example echo
					}
					//printf("input_list->input = %s\n", temp->input);
					temp = temp->next;
				}
				clear_input(data.input_list, SUCCESS);
			}
			else
			{
				clear_env_list(data.env_list, SUCCESS);
				break ;
			}
			add_history(input);
		}
		free(input);
		input = NULL;
	}
	rl_clear_history();
}
