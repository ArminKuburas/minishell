/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 08:58:03 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/10 17:44:55 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// If exit is called with a numeric argument, the shell exits with that specific exit status.
// This exit status should be an integer in the range of 0 to 255.

/*
bash-3.2$ exit donkey
exit
bash: exit: donkey: numeric argument required
*/

/*The range of 0 to 255 provides a wide range of values to differentiate between different types of errors or failure conditions.
While the exact meaning of each non-zero exit status can vary depending on the application or script, programmers often assign specific
exit codes to different types of errors to facilitate error handling and debugging.*/

/*
At the start of the string you are allowed to include one - or + character. If any other non numeric character exists either at the start of afterwards you make it return a fail (255) plus printing out a string that says some bullshit lol

perhaps osmething like

if ft_strchr("-+", string[0]) || ft_is_itnumber(orwhatever the fuck that libft function is called again lol, string[0])


now you have two options I think.

either have it be longlong (basically a variable double the size of long.) and just have a check that if the value at the end is more than   9223372036854775807 or less than -9223372036854775808

return 255 and print the error message.

otherwise you just return the given longlong as a unsigned char (I know it sound sus as fuck but listen)

a char is one byte. an unsigned char would then only go from 0 to 255. Which is the range we work with when we exit. So if you shove a long into a unsigned char then it would underflow or overflow as needed. So something like 256 would become 0 or whatever the fuck.
*/

// always check the length of the string to do the initial atoi check

int	is_it_numeric(t_shelldata *data, char **inputs)
{
	int	i;

	i = 0;
	while (inputs[1][i] != '\0')
	{
		if (ft_isdigit(inputs[1][i]) == 0)
		{
			data->exit_value = 255;
			ft_putstr_fd("bananashell: exit: ", 2);
			ft_putstr_fd(inputs[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (data->exit_value);
		}
		i++;
	}
	return (data->exit_value);
}

int	sign_fail(t_shelldata *data, char *input)
{
	data->exit_value = 255;
	ft_putstr_fd("bananashell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (data->exit_value);
}

int	sign_check(t_shelldata *data, char *input, int i, int sign)
{
	int	count;

	count = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '+' || input[i] == '-')
		{
			if (input[i] == '+')
			{
				count++;
				sign = 0;
			}
			if (input[i] == '-')
			{
				count++;
				sign = 1;
			}
			if (count > 1)
				return (sign_fail(data, input));
		}
		i++;
	}
	data->exit_value = 0;
	return (data->exit_value);
}

int	check_format(t_shelldata *data, char **inputs)
{
	int	i;

	i = 0;
	if (sign_check(data, inputs[1], 0, 0) != 0)
		return (data->exit_value);
	if (is_it_numeric(data, inputs) != 0)
		return (data->exit_value);
	if (inputs[1] && inputs [2])
	{
		ft_putendl_fd("bananashell: exit: too many arguments", 2);
		data->exit_value = 1;
		return (data->exit_value);
	}
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
