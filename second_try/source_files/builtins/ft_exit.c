/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/11 00:05:31 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	num_fail(t_shelldata *data, char *input)
{
	data->exit_value = 255;
	ft_putstr_fd("bananashell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (data->exit_value);
}

int	is_it_numeric(t_shelldata *data, char *input)
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
	return (data->exit_value);
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

int	ft_atol(const char *str)
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
	if (sign == -1 || result == 0)
		return (0);
	if (sign == 1 && result == -1)
		return (0);
	result = ft_parse_digits(str, sign);
	return ((long)(result * sign));
}

int	check_format(t_shelldata *data, char **inputs)
{
	if (is_it_numeric(data, inputs[1]) != 0)
		return (data->exit_value);
	if (inputs[1] && inputs [2])
	{
		ft_putendl_fd("bananashell: exit: too many arguments", 2);
		data->exit_value = 1;
		return (data->exit_value);
	}
	if (ft_atol(inputs[1]) == 0 && inputs[1][0] != '0')
		return (num_fail(data, inputs[1]));
	data->exit_value = (unsigned char)ft_atol(inputs[1]);
	return (data->exit_value);
}

int	ft_exit(t_shelldata *data, char **inputs)
{
	if (!inputs[1])
	{
		data->exit_value = 0;
		return (data->exit_value);
	}
	data->exit_value = check_format(data, inputs);
	return (data->exit_value);
}
