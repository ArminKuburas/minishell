/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:01 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/17 21:50:15 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function should parse the export arguments into env_var_name and env_var_value pairs*/
// export TEST=value, becomes TEST=value when printenv | awk -F= '{print $0}'
// export TEST_VALUE1======value1 becomes TEST_VALUE1======value1 when printenv | awk -F= '{print $0}'
// so we can say that the amont of equal signs does not matter, but the first one is the separator

// though when we printenv | awk -F= '{print $2}' the TEST=value became value
// but on the env list index of TEST_VALUE1======value1 is nothing when we printenv | awk -F= '{print $2}'
// I dont know if this is what we need to take into consideration, it seems if there are more than one equal sign
// the value is not printed, but the env_var_name is printed correctly

//Variable names must start with a letter (a-z or A-Z) or an underscore (_).
//After the first character, variable names can contain letters, numbers, or underscores.
//Variable names cannot contain spaces or special characters such as !, @, #, $, %, etc. except for underscore.

// valid examples:
// my_var
// _var
// var123

// invalid examples:
// 123var (starts with a number)
// var! (contains a special character)
// my var (contains a space), actually becomes var=

// Variable values can generally contain any character, 
// except for the null character (\0) and the newline character (\n), 
// as these characters are used for string termination and separation, respectively.

// export my var=TEST gives valid result, even it contains space.
// we could propably make a check that if input count more than 2 before the = sign to see if the 
// env name is valid.

// export my fucking test var= value becomes var= , so space after the =
// makes the value string non-existent.

static int	is_var_name_valid(t_input_list *temp)
{
	int i;

	i = 0;
	if (!ft_isalpha(temp->next->input[i]) && temp->next->input[i] != '_')
		return (0);
	while (temp->next->input[i] && temp->next->input[i] != '=')
	{
		if (ft_isalnum(temp->next->input[i]) || temp->next->input[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

static void export_no_commands(t_shelldata data)
{
	if (!data.env_list)
		return ;
	while(data.env_list)
	{
		ft_printf("declare -x %s\n", data.env_list->env_var);
		data.env_list = data.env_list->next;
	}
}

static void	is_env_existent(t_shelldata data, t_input_list *temp)
{
	char	*temp;

	while (temp)
	{
		while (ft_strchr(temp->input, '=') == NULL)
			temp = temp->next;
	}
	while (data.env_list)
	{
		if (ft_strnstr(data.env_list->env_var_name, temp->input, \
		ft_strlen(data.env_list->env_var_name)))

	}
}

void	my_export(t_shelldata data, t_input_list *temp)
{
	if (!temp->next)
	{
		export_no_commands(data);
		return ;
	}
	while (data.env_list)
	{
		if (is_var_name_valid(temp) == 0)
		{
			ft_printf("ERROR IN EXPORT\n");
			return ;
		}
		else
		{
			// add a check for already existing env name
			is_env_existent(data, temp);
		}
		data.env_list = data.env_list->next;
	}
	ft_printf("export\n");
}
