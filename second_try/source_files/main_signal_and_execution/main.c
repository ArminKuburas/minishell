/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/08 12:59:05 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>

// when in heredoc and CTR+C the ^C will not display
// when in bash and you have inputted cat for example, then you CTRL+C the ^C will display
// without prompt.
// When terminal is opened for the first time and you do CTRL+C in bash, the ^C is shown for once,
// need to figure out why.
// CTRL + \ = SIGQUIT

int	check_argc_argv(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putendl_fd("Too many arguments", STDERR_FILENO);
		return (FAILURE);
	}
	if (argc < 1)
	{
		ft_putendl_fd("How did you do that?", STDERR_FILENO);
		return (FAILURE);
	}
	if (argv[0] == NULL)
	{
		ft_putendl_fd("What. How did you do that? A null name?", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	end_of_file_reached(t_shelldata *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	clear_env_list(data->env_list, SUCCESS);
	free(data->pwd);
	free(data->env_variables);
	rl_clear_history();
	exit(0);
}

int	set_up_data(t_shelldata *data)
{
	if (data->input == NULL)
		return (FAILURE);
	if (ft_strlen(data->input) == 0)
		return (FAILURE);
	if (new_mini_split(data) != SUCCESS)
		return (FAILURE);
	input_type_assigner(data->input_list);
	if (check_pipes(data) != SUCCESS)
		return (FAILURE);
	split_cleaner(data);
	set_up_child_data(data);
	return (SUCCESS);
}

void	main_loop(t_shelldata *data)
{
	while (1)
	{
		parent_signals();
		data->input = readline(YELLOW"🍌bananashell-0.23:"RESET);
		if (!data->input)
			end_of_file_reached(data);
		if (set_up_data(data) != SUCCESS)
		{
			free(data->input);
			continue ;
		}
		child_handling(data);
		add_history(data->input);
		free(data->input);
		data->input = NULL;
		clear_input(data->input_list, SUCCESS);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shelldata	data;

	ft_memset(&data, 0, sizeof(t_shelldata));
	if (initial_setup(&data, argc, argv, env) == FAILURE)
		return (FAILURE);
	main_loop(&data);
	rl_clear_history();
	return (0);
}
