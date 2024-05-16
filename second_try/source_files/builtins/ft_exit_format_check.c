/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_format_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:47:25 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/14 14:07:22 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/**
 * @file ft_exit_format_check.c
 * @brief Functions for checking the format of the exit command.
*/

/**
 * @brief prints error message if the input is not a number.
 * @param data main struct for the program.
 * @param input the input string.
 */
static int	is_it_numeric(t_shelldata *data, char *input)
{
	int	i;

	i = 0;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (input[i] == '+' || input[i] == '-' || input[i] == '\0')
	{
		num_fail(data, input);
		return (255);
	}
	while (input[i] != '\0')
	{
		if (ft_isdigit(input[i]) == 0)
		{
			num_fail(data, input);
			return (255);
		}
		i++;
	}
	return (0);
}

/**
 * @brief parses the given digits from the input string.
 * @param str the input string.
 * @param sign the sign of the number positive or negative.
 * @return the parsed number.
*/
static long	ft_parse_digits(const char *str, int sign)
{
	long long	result;
	long long	temp;

	result = 0;
	temp = 0;
	while (*str >= '0' && *str <= '9')
	{
		temp = result;
		result = result * 10 + (*str - '0');
		if (sign == 1 && temp > result)
			return (-1);
		else if (sign == -1 && temp > result)
			return (0);
		str++;
	}
	return (result);
}

/**
 * @brief converts the input string to a long long and sets the exit value.
 * @param data main struct for the program.
 * @param str the input string.
 * @param input the input string.
*/
static void	ft_atol(t_shelldata *data, const char *str, char *input)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = ft_parse_digits(str, sign);
	if (sign == -1 && result == 0 && *str != '0')
		num_fail(data, input);
	if (sign == 1 && result == -1 && *str != '-' && *str++ != '+')
		num_fail(data, input);
	result = (result * sign) % 256;
	if (result < 0)
		result += 256;
	data->exit_value = ((int)(result));
}

/**
 * @brief checks the format of the exit command.
 * @param data main struct for the program.
 * @param inputs array of strings from the input.
*/
void	check_format(t_shelldata *data, char **inputs)
{
	if (is_it_numeric(data, inputs[1]) != 0)
		return ;
	if (inputs[1] && inputs[2])
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("bananashell: exit: too many arguments", 2);
		data->exit_value = 1;
		return ;
	}
	if (ft_strcmp(inputs[1], "-9223372036854775808") == 0)
	{
		data->exit_value = 0;
		clean_exit(data, 1);
	}
	ft_atol(data, inputs[1], inputs[1]);
	clean_exit(data, 1);
}
