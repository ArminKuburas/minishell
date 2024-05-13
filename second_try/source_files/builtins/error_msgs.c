/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:41:38 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/14 02:21:36 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file error_msgs.c
 * @brief Functions for printing error messages.
*/

/**
 * @brief Prints error message for a failed malloc.
 * @param data The struct containing shell data.
 * @param input The input that caused the error.
*/
void	num_fail(t_shelldata *data, char *input)
{
	data->exit_value = 255;
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bananashell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	clean_exit(data, 0);
}
