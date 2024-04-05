/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid_with_getenv_func.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:46:41 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/03 12:19:33 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*pid_strl;
	int		pid;

	pid_strl = getenv("$$");
	if (pid_strl != NULL)
	{
		pid = atoi(pid_strl);
		printf("My PID is: %d\n", pid);
	}
	else
	{
		printf("Failed to retrieve PID.\n");
	}
	return (0);
}