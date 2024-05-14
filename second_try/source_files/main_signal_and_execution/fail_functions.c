/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:16:19 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/14 15:27:30 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*This place will contain versions of external functions that always fail
For example fake_malloc or fake_dup2 to see the results when I replace
the regular version with the fake version.
A stress test for memory failures, etc. for example a malloc that only returns
NULL.*/

void	*fake_ft_calloc(int amount, int size)
{
	amount = 0;
	size = 0;
	errno = ENOMEM;
	return (NULL);
}

int	fake_open(void)
{
	errno = EACCES;
	return (-1);
}

int	fake_dup2(void)
{
	errno = EBADF;
	return (-1);
}

int	fake_fork(void)
{
	errno = EAGAIN;
	return (-1);
}
