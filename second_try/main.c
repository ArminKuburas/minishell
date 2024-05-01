/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:09 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/01 09:57:26 by akuburas         ###   ########.fr       */
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
		error = update_shell_level(&data);
		if (error != SUCCESS)
		{
			clear_env_list(data.env_list, FAILURE);
			return (FAILURE);
		}
		error = create_exit_value_env(&data);
		if (error != SUCCESS)
		{
			clear_env_list(data.env_list, FAILURE);
			return (FAILURE);
		}
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
		//remove_from_env_list(&data, "PATH");
		//remove_from_env_list(&data, "LS_COLORS");
		//create_2d_env(&data);
		temp = data.env_list;
		printf("after remove\n");
		printf("--------------------\n\n\n\n");
		while (temp != NULL)
		{
			printf("--------------------\n");
			printf("env_var = %s\n", temp->env_var);
			printf("env_var_name = %s\n", temp->env_var_name);
			printf("env_var_value = %s\n", temp->env_var_value);
			printf("--------------------\n");
			temp = temp->next;
		}
		int z = 0;
		while (data.env_variables[z] != NULL)
		{
			printf("This is data.env_variables[%d] = %s\n", z, data.env_variables[z]);
			z++;
		}
		printf("--------------------\n");
	}
	while (1)
	{
		parent_signals();
		data.pwd = getcwd(NULL, 0);
		if (!data.pwd)
			ft_putendl_fd("Fail in getcwd", 2);
		data.input = readline("bananashell-0.21:");
		if (!data.input)
		{
			if (errno != 0)
				ft_putendl_fd("Fail in readline", STDERR_FILENO);
			else
				printf("exit");
			clear_env_list(data.env_list, SUCCESS);
			free(data.env_variables);
			free(data.pwd);
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
						if (data.child_data[i].command_inputs != NULL && data.child_data[i].command != NULL)
						{
							while (data.child_data[i].command_inputs[x] != NULL)
							{
								printf("This is command inputs inside child data %d: command inputs %x = %s\n", i, x, data.child_data[i].command_inputs[x]);
								x++;
							}
						}
						else
							printf("child %d command inputs are NULL\n", i);
						x = 0;
						i++;
					}
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
				printf("--------------------\n");
				clear_input(data.input_list, SUCCESS);
			}
			add_history(data.input);
		}
		free(data.input);
		data.input = NULL;
		free(data.pwd);
		data.pwd = NULL;
		if (error == FAILURE)
			break ;
	}
	rl_clear_history();
}
