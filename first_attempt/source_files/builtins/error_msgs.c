/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:41:38 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/24 12:22:01 by tvalimak         ###   ########.fr       */
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
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	clean_exit(data, 0);
}

/**
 * @brief checks if the given path is a directory.
 * @param path The path to be checked.
 * @return Returns YES if the path is a directory, otherwise NO.
*/
int	cd_check_if_directory(char *path)
{
	int	directory_check;

	directory_check = open(path, O_DIRECTORY);
	if (directory_check == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
		return (NO);
	}
	close(directory_check);
	return (YES);
}
