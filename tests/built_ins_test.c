/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:14:37 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/10 18:06:10 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../first_try/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_ENV_VARS 100
#define MAX_ENV_VAR_LENGTH 100
#define	MAX_PATH_LENGTH 4096

char *env[MAX_ENV_VARS];
int env_count = 0;

// compilation with hcc built_ins_test.c /Users/tvalimak/minishell/first_try/libft/libft.a

void	my_cd(char *args[])
{
	if (args[1] == NULL)
	{
    // If no directory is provided, go to the home directory
	printf("%s\n", getenv("HOME"));
    //chdir(getenv("HOME"));
	chdir("./hakemisto");
    }
	else
	{
        if (chdir(args[1]) != 0)
		{
            // Error handling if chdir fails
            perror("chdir");
        }
    }
}

static void		free_to_print(char *args[], int i)
{
	while (args[i] != NULL)
    {
        ft_printf("%s ", args[i]);
        i++;
    }
        ft_printf("\n");
}

static void    my_echo(char *args[])
{
	int i;

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


void my_pwd(char *args[])
{
	char *cwd;
	char buff[MAX_PATH_LENGTH];

	args = NULL;
	cwd = getcwd(buff, MAX_PATH_LENGTH);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
	}
}

void execute_command(char *command[])
{
    if (strcmp(command[0], "echo") == 0)
        my_echo(command);
	if (strcmp(command[0], "cd") == 0)
		my_cd(command);
	if (strcmp(command[0], "pwd") == 0)
		my_pwd(command);
	/*
    else
    {
        // Execute external command here
        // For simplicity, you can use execvp to execute external commands
        //execvp(command[0], command);
        //perror("execvp");
    }*/
}

int main(int argc, char *argv[], char *envp[])
{
	if (argc > 1)
	{
		int i = 0;

		while (i < MAX_ENV_VARS && envp[i] != NULL)
		{
			env[i] = strdup(envp[i]);
			env_count++;
			i++;
		}
		execute_command(argv + 1); // execute_command(argv + 1);
		//my_echo(argv);
	}
	return (0);
}
