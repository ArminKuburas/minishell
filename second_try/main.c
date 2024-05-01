/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/01 12:05:34 by akuburas         ###   ########.fr       */
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

int	new_env_node(t_env_list *old_node, char *env_var_name, char *env_var_value)
{
	t_env_list	*new_node;
	char		*temp;

	new_node = ft_calloc(1, sizeof(t_env_list));
	if (!new_node)
		return (NO_MEMORY);
	old_node->next = new_node;
	new_node->env_var_name = env_var_name;
	new_node->env_var_value = env_var_value;
	temp = ft_strjoin(env_var_name, "=");
	if (!temp)
		return (NO_MEMORY);
	new_node->env_var = ft_strjoin(temp, env_var_value);
	free(temp);
	if (!new_node->env_var)
		return (NO_MEMORY);
	return (SUCCESS);
}

int	create_question_node(t_shelldata *data, t_env_list *temp)
{
	char	*env_var_name;


	env_var_name = ft_strdup("?");
	if (!env_var_name)
		return (NO_MEMORY);
	return (new_env_node(temp, env_var_name, ft_itoa(data->exit_value)));
}

int	create_exit_value_env(t_shelldata *data)
{
	t_env_list	*temp;

	temp = data->env_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->env_var_name, "?") == 0)
		{
			free (temp->env_var_value);
			temp->env_var_value = ft_itoa(data->exit_value);
			if (!temp->env_var_value)
				return (NO_MEMORY);
			return (SUCCESS);
		}
		if (temp->next == NULL)
			return (create_question_node(data, temp));
		temp = temp->next;
	}
	return (FAILURE);
}

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

int	initial_env_creation(char **env, t_shelldata *data)
{
	int	error;

	error = duplicate_env(env, &data);
	if (error != SUCCESS)
		return (FAILURE);
	error = update_shell_level(&data);
	if (error != SUCCESS)
	{
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	error = create_exit_value_env(&data);
	if (error != SUCCESS)
	{
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
	//remove_from_env_list(&data, "PATH");
	//remove_from_env_list(&data, "LS_COLORS");
	//create_2d_env(&data);
}

int initial_setup(t_shelldata *data, int argc, char **argv, char **env)
{

	if (check_argc_argv(argc, argv) == FAILURE)
		return (FAILURE);
	if (env)
		if (initial_env_creation(env, &data) == FAILURE)
			return (FAILURE);
	if (!data->pwd)
	{
		ft_putendl_fd("getcwd has failed", 2);
		clear_env_list(data->env_list, FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	end_of_file_reached(t_shelldata *data)
{
	ft_putstr("exit");
	clear_env_list(data->env_list, SUCCESS);
	free(data->env_variables);
	free(data->pwd);
	clear_input(data->input_list, SUCCESS);
	rl_clear_history();
	exit(0);
}

void	set_up_data(t_shelldata *data)
{
	int	error;

	/*Continue work from here. Its gonna be a lot lol*/
	new_mini_split(&data);
	input_type_assigner(data->input_list);
	if (check_pipes(data) != SUCCESS)
		exit_time(data, FAILURE);
	if (split_cleaner(data) != SUCCESS)
		exit_time(data, FAILURE);
	if (error != SUCCESS)
	{
		clear_input(data->input_list, FAILURE);
		free(data->input);
		data->input = NULL;
	}
	else
	{
	error = set_up_child_data(&data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shelldata	data;
	int			error;

	data = (t_shelldata){0};
	if (initial_setup(&data, argc, argv, env) == FAILURE)
		return (FAILURE);
	while (1)
	{
		parent_signals();
		data.input = readline("bananashell-0.21:");
		if (!data.input)
			end_of_file_reached(&data);
		if (ft_strlen(data.input) == 0)
		{
			free(data.input);
			continue ;
		}
		set_up_data(&data)
		error = new_mini_split(&data);
		if (error == SUCCESS)
		{
			error = set_up_child_data(&data);
			error = child_pre_check(&data);
			error = create_exit_value_env(&data);
			if (error != SUCCESS)
			{
				clear_env_list(data.env_list, FAILURE);
				free(data.env_variables);
				free(data.pwd);
				free(data.input);
				clear_input(data.input_list, FAILURE);
				break ;
			}
		}
		clear_input(data.input_list, SUCCESS);
		add_history(data.input);
		free(data.input);
		data.input = NULL;
		free(data.pwd);
		data.pwd = NULL;
		if (error == FAILURE)
			break ;
	}
	rl_clear_history();
}
