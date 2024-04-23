/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/23 22:22:20 by tvalimak         ###   ########.fr       */
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
		data.pwd = getcwd(NULL, 0);
		if (!data.pwd)
			ft_putendl_fd("Fail in getcwd", 2);
		data.input = readline("bananashell-0.14:");
		if (!data.input)
		{
			printf("exit\n");
			rl_clear_history();
			clear_env_list(data.env_list, SUCCESS);
			break ;
		}
		if (data.input)
		{
			if (ft_strlen(data.input) == 0)
			{
				free(data.input);
				continue ;
			}
			error = new_mini_split(&data);
			if (error == SUCCESS)
			{
				t_input_list *temp = data.input_list;
				t_input_list *data_head = temp;
				int i = 0;
				while (temp != NULL)
				{
					printf("This is input %d: %s\n", i, temp->input);
					i++;
					temp = temp->next;
				}
				temp = data_head;
				if (temp->next && temp->next->type == REDIRECT_HEREDOC)
					heredoc(data, temp);
				if (ft_strcmp(temp->input, "pwd") == 0)
				{
					my_pwd(data, temp);
					free(data.input);
					continue ;
				}
				if (ft_strcmp(temp->input, "cd") == 0)
				{
					my_cd(data, temp);
					free(data.input);
					continue ;
				}
				if (ft_strcmp(temp->input, "exit") == 0)
				{
					printf("exit\n");
					free(data.input);
					clear_env_list(data.env_list, SUCCESS);
					break ;
				}
				clear_input(data.input_list, SUCCESS);
			}
			add_history(data.input);
		}
		free(data.input);
		data.input = NULL;
	}
	rl_clear_history();
}
