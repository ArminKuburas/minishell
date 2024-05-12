/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_format_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 12:47:25 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/12 12:49:56 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_it_numeric(t_shelldata *data, char *input)
{
	int	i;

	i = 0;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (input[i] == '+' || input[i] == '-' || input[i] == '\0')
		return (num_fail(data, input));
	while (input[i] != '\0')
	{
		if (ft_isdigit(input[i]) == 0)
			return (num_fail(data, input));
		i++;
	}
	return (0);
}

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

static int	ft_atol(t_shelldata *data, const char *str, char *input)
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
		return (num_fail(data, input));
	if (sign == 1 && result == -1 && *str != '-' && *str++ != '+')
		return (num_fail(data, input));
	result = (result * sign) % 256;
	if (result < 0)
		result += 256;
	return ((int)(result));
}

int	check_format(t_shelldata *data, char **inputs)
{
	if (is_it_numeric(data, inputs[1]) != 0)
		return (data->exit_value);
	if (inputs[1] && inputs[2])
	{
		ft_putendl_fd("bananashell: exit: too many arguments", 2);
		data->exit_value = 1;
		return (data->exit_value);
	}
	if (ft_strcmp(inputs[1], "-9223372036854775808") == 0)
	{
		data->exit_value = 0;
		return (data->exit_value);
	}
	data->exit_value = ft_atol(data, inputs[1], inputs[1]);
	return (data->exit_value);
}