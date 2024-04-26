/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/26 03:45:15 by akuburas         ###   ########.fr       */
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
	t_shelldata	data;
	int			error;


	ft_memset(&data, 0, sizeof(t_shelldata));
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
		data.input = readline("bananashell-0.17:");
		if (!data.input)
		{
			printf("exit");
			clear_env_list(data.env_list, SUCCESS);
			break ;
		}
		if (data.input)
		{
			if (ft_strcmp(data.input, "exit") == 0)
			{
				printf("exit\n");
				free(data.input);
				clear_env_list(data.env_list, SUCCESS);
				break ;
			}
			if (ft_strlen(data.input) == 0)
			{
				free(data.input);
				continue ;
			}
			error = new_mini_split(&data);
			if (error == SUCCESS)
			{
				t_input_list *temp = data.input_list;
				int i = 0;
				while (temp != NULL)
				{
					printf("This is input %d: %s\n", i, temp->input);
					printf("This is word_split %d: %d\n", i, temp->word_split);
					printf("This is type = %d\n", temp->type);
					i++;
					temp = temp->next;
				}
				printf("--------------------\n");
				error = set_up_child_data(&data);
				i = 0;
				int x = 0;
				printf("--------------------\n");
				if (error == SUCCESS)
				{
					while (i < data.command_amount)
					{
						printf("This is command %d: %s\n", i, data.child_data[i].command);
						printf("This is fd_in %d: %d\n", i, data.child_data[i].fd_in);
						printf("This is fd_out %d: %d\n", i, data.child_data[i].fd_out);
						printf("This is pipe fd out 0 and 1: %d %d\n", data.child_data[i].p_fd_out[0], data.child_data[i].p_fd_out[1]);
						printf("This is pipe fd in 0 and 1: %d %d\n", data.child_data[i].p_fd_in[0], data.child_data[i].p_fd_in[1]);
						printf("This is exit value %d: %d\n", i, data.child_data[i].exit_value);
						while (data.child_data[i].command_inputs && data.child_data[i].command_inputs[x] != NULL)
						{
							printf("This is command inputs inside child data %d: command inputs %x = %s\n", i, x, data.child_data[i].command_inputs[x]);
							x++;
						}
						x = 0;
						free_child_data(&data.child_data[i]);
						i++;
					}
					free(data.child_data);
				}
				printf("--------------------\n");
				clear_input(data.input_list, SUCCESS);
			}
			add_history(data.input);
		}
		free(data.input);
		data.input = NULL;
	}
	rl_clear_history();
}
