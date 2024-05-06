/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:00:04 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 12:00:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char *string = "Hello, World!";
	int	i = 0;
	while(string[i] != '=')
	{
		printf("%c", string[i]);
		i++;
	}

	return (0);
}