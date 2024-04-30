/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 07:06:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/30 07:08:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	const	char 	*program_path = "/bin/ls";
	char *const		argv[] = { "/bin/ls", "-l", NULL };
	char *const argv2[] = {NULL};
	char *const envp[] = {NULL};
	char **example;
	char **example2;

	example = NULL;
	example2 = NULL;

	if (execve(program_path, example, example2) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	printf("This won't be reached!\n");
	return (0);
}