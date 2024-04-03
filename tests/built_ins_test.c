/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:14:37 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/03 18:33:07 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_ENV_VARS 100
#define MAX_ENV_VAR_LENGTH 100

char *env[MAX_ENV_VARS];
int env_count = 0;

void my_echo(char *args[])
{
	int i = 1;
	while (args[i] != NULL)
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
}
void execute_command(char *command[])
{
    if (strcmp(command[0], "echo") == 0)
    {
        my_echo(command);
	}
    else
    {
        // Execute external command here
        // For simplicity, you can use execvp to execute external commands
        execvp(command[0], command);
        perror("execvp");
    }
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
		execute_command(argv + 1);
		//my_echo(argv);
	}
	return (0);
}
