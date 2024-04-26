/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:47:41 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/26 14:06:00 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static long	parse_digits(const char *str, int sign)
{
	long	result;
	long	temp;

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

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

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
	result = parse_digits(str, sign);
	return ((int)(result * sign));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	main(int argc, char ** argv)
{
	int	x;

	x = ft_atoi(argv[1]);
	printf("This is x = %d\n", x);
	printf("This is ft_isdigit['1'] = %d\n", ft_isdigit('1'));
	return (0);
}