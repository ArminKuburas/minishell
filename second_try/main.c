/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/10 22:33:12 by akuburas         ###   ########.fr       */
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

static void	signal_handler(int signal)
{
	if (signal == CTRL_C)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	carrot_toggle(int on)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (!on)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	set_state(t_state state)
{
	if (state == DEFAULT)
	{
		carrot_toggle(1);
	}
	if (state == HEREDOC)
	{
		return ;
	}
	if (state == HANDLER)
	{
		carrot_toggle(0);
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
	if (env)
	{
		error = duplicate_env(env, &data);
		if (error != SUCCESS)
			return (FAILURE);
		t_env_list	*temp = data.env_list;
		while (temp != NULL)
		{
			printf("env_var = %s\n", temp->env_var);
			printf("env_var_name = %s\n", temp->env_var_name);
			printf("env_var_value = %s\n", temp->env_var_value);
			temp = temp->next;
		}
	}
	while (1)
	{
		set_state(HANDLER);
		//set_state(DEFAULT);
		signal(CTRL_C, signal_handler);
		input = readline("bananashell-0.10:");
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
				clear_env_list(data.env_list, SUCCESS);
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
