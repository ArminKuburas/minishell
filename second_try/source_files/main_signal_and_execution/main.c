/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/20 14:10:33 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file main.c
 * @brief Main file for the minishell program.
 * @details This file contains the main function and the main loop.
*/

/**
 * @brief Quickly checks the argc and argv.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/	
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

/**
 * @brief Sets up the data for the minishell.
 * @param data The data to be set up.
 * @return Returns SUCCESS if everything went well, otherwise FAILURE.
*/

int	set_up_data(t_shelldata *data)
{
	if (data->input == NULL)
		return (FAILURE);
	if (ft_strlen(data->input) == 0)
		return (SUCCESS);
	if (new_mini_split(data) != SUCCESS)
		return (FAILURE);
	input_type_assigner(data->input_list);
	if (check_pipes(data) != SUCCESS)
		return (FAILURE);
	split_cleaner(data);
	set_up_child_data(data);
	return (SUCCESS);
}

/**
 * @brief The main loop for the minishell program.
 * @param data The data for the minishell.
 * @return void
*/
void	main_loop(t_shelldata *data)
{
	while (1)
	{
		loop_helper(data);
		if (ft_strlen(data->input) == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		if (set_up_data(data) != SUCCESS)
		{
			free(data->input);
			exit(1);
		}
		if (g_exit_value != 0)
		{
			g_exit_value = 0;
			continue ;
		}
		child_handling(data);
		free(data->input);
		data->input = NULL;
		clear_input(data->input_list, SUCCESS);
	}
}

/**
 * @brief The main function for the minishell program.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @param env The environment variables.
 * @return Returns 0 if everything went well, otherwise 1.
*/
int	main(int argc, char **argv, char **env)
{
	t_shelldata		data;

	ft_memset(&data, 0, sizeof(t_shelldata));
	if (initial_setup(&data, argc, argv, env) == FAILURE)
		return (FAILURE);
	main_loop(&data);
	rl_clear_history();
	return (0);
}
