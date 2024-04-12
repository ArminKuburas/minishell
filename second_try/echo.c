/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:55:23 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/12 16:38:51 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_to_print(char *args[], int i)
{
	while (args[i] != NULL)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("\n");
}

void	my_echo(char *args[])
{
	int	i;

	i = 1;
	if (!args[i])
		ft_printf("\n");
	else if (ft_strncmp(args[i], "-n", 3) == 0)
	{
		while (ft_strncmp(args[i], "-n", 3) == 0)
			i++;
		while (args[i] != NULL)
		{
			if (args[i + 1] == NULL)
				ft_printf("%s", args[i]);
			else
				ft_printf("%s ", args[i]);
			i++;
		}
	}
	else
		free_to_print(args, i);
}

void execute_command(char *command[])
{
	//char builtin[4][7];

	//builtin[0] = "echo";
    if (ft_strcmp(command[0], "echo") == 0)
        my_echo(command);
	//if (ft_strcmp(command[0], "cd") == 0)
	//	my_cd(command);
	//if (ft_strcmp(command[0], "pwd") == 0)
	//	my_pwd(command);
	//if (ft_strcmp(command[0], "export") == 0)
	//{
	//	if (command[1] == NULL)
	//		print_env();
	//	else
	//		export_env(command);
}
	//if (strcmp(command[0], "unset") == 0)
	//if (strcmp(command[0], "env") == 0)
	//if (strcmp(command[0], "exit") == 0)
	//	exit(0);
	/*
    else
    {
        // Execute external command here
        // For simplicity, you can use execvp to execute external commands
        //execvp(command[0], command);
        //perror("execvp");
    }*/
