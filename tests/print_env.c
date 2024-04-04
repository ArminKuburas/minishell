/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:18:43 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/04 15:20:12 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	printf("Environment variables:\n");
	for (int i = 0; envp[i] != NULL; i++)
		printf("%s\n", envp[i]);
	return (0);
}
