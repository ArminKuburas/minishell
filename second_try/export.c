/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:01 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/26 16:37:11 by tvalimak         ###   ########.fr       */
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
/*
static int	is_var_name_valid(t_input_list *temp)
{
	int	i;

	i = 0;
	if (!ft_isalpha(temp->next->input[i]) && temp->next->input[i] != '_')
		return (0);
	while (temp->next->input[i] && temp->next->input[i] != '=' && \
	(ft_strlen(temp->next->input) > 1))
	{
		if (ft_isalnum(temp->next->input[i]) || temp->next->input[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}*/
/*
bash-3.2$ export asd!=val! asd1=val1 asd2=val2
bash: export: `asd!=val!': not a valid identifier
in this case only the asd1=val1 gets ignored, asd1 and asd2 still gets
exported.

bash-3.2$ export !@# asd1=val1 asd2=val2
bash: !@#: event not found

bash-3.2$ export !#
export export

 first we need to check that does the current node input contain '='
 if it doesn't but the node input string is valid for export name,
 we can keep on iterating the nodes until we end up with one that
 contains the '=' or we end in last node.
 if there are input nodes after the one with = but they are not formatted
 for example like: export asd1=val1 das asd dsa would only become asd1=val1,
 unless its formatted like export asd1="val1 das asd dsa" when it becomes
 asd1=val1 das asd dsa.
 */

// remember to check exit code when error handling takes place
/*This function checks all arguments for export and flags them if
  they are good for execution*/

/*Valid input tag is 84 and invalid is 85*/
/*
static void	ft_export_type_printer(t_input_list *temp)
{
	while (temp)
	{
		ft_printf("type of the input node: %d\n", temp->type);
		ft_printf("string in the input node: %s\n", temp->input);
		temp = temp->next;
	}
}*/
/*This one checks if the export command is formatted properly*/

static void	is_export_var_name_valid(t_input_list *temp)
{
	int	i;

	i = 0;
	if (!ft_isalpha(temp->input[i]) && temp->input[i] != '_')
	{
		ft_printf("bananashell: export: `%s': not a valid identifier\n", \
		temp->input);
		temp->type = INVALID_EXPORT_INPUT;
		return ;
	}
	while (temp->input[i] != '\0' && temp->input[i] != '=')
	{
		if (ft_isalnum(temp->input[i]) || temp->input[i] == '_')
			i++;
		else
		{
			temp->type = INVALID_EXPORT_INPUT;
			ft_printf("bananashell: export: `%s': not a valid identifier\n", \
			temp->input);
			return ;
		}
	}
	temp->type = VALID_EXPORT_INPUT;
}

/*Function to imitate export command without arguments*/
static void	export_no_commands(t_shelldata *data)
{
	// the formatting of the output needs reworking
	if (!data->env_list)
		return ;
	while (data->env_list)
	{
		ft_printf("declare -x %s\n", data->env_list->env_var);
		data->env_list = data->env_list->next;
	}
}

/*This one goes through the env list and sees if the new env var
  already exists*/
  /*		if (!ft_strncmp(data->env_list->env_var_name, temp->input, \
		ft_strlen(data->env_list->env_var_name)))*/
		// ft_strrchr(args[1], (int)'=')
static int	check_if_export_env_exists(t_shelldata *data, t_input_list *temp)
{
	ft_printf("got into the check_if_env_exists\n");
	while (data->env_list->next)
	{
		if (!ft_strncmp(data->env_list->env_var_name, temp->input, \
		ft_strlen(temp->input)))
		{
			ft_printf("env found\n");
			return (1);
		}
		data->env_list = data->env_list->next;
	}
	return (0);
}

/*This function adds a new env var to the env list*/
static void	add_new_env_var(t_shelldata *data, t_input_list *temp)
{
	t_env_list	*new_env;
	t_env_list	*temp_env;

	new_env = ft_calloc(1, sizeof(t_env_list));
	if (!new_env)
		return ;
	new_env->env_var_name = ft_strdup(temp->input);
	new_env->env_var_value = ft_strdup(temp->input);
	new_env->env_var = ft_strdup(temp->input);
	new_env->next = NULL;
	temp_env = data->env_list;
	while (temp_env->next)
		temp_env = temp_env->next;
	temp_env->next = new_env;
}

/*This function replaces the env var value if it already exists*/
static void replace_env_var(t_shelldata *data, t_input_list *temp)
{
	t_env_list	*temp_env;

	temp_env = data->env_list;
	while (temp_env)
	{
		if (!ft_strncmp(temp_env->env_var_name, temp->input, \
		ft_strlen(temp_env->env_var_name)))
		{
			temp_env->env_var_value = ft_strdup(temp->input);
			temp_env->env_var = ft_strdup(temp->input);
			break ;
		}
		temp_env = temp_env->next;
	}
}

/*  This function will go through the input list and figures out do we
    replace or add the new key/value pair */
static void	execute_export_commands(t_shelldata *data, t_input_list *temp)
{
	char	*value_index;

	while (temp)
	{
		if (temp->type == VALID_EXPORT_INPUT)
		{
			value_index = ft_strchr(temp->input, 075);
			if (value_index != NULL)
			{
				if (check_if_export_env_exists(data, temp) == 1)
				{
					replace_env_var(data, temp);
					break ;
				}
				else
				{
					add_new_env_var(data, temp);
					break ;
				}
			}
		}
		temp = temp->next;
	}
}
/* my_export main function*/
void	my_export(t_shelldata *data, t_input_list *temp)
{
	t_input_list	*input_head;
	t_env_list		*env_head;
	t_shelldata		*data_head;

	env_head = data->env_list;
	input_head = temp;
	data_head = data;
	if (!temp->next)
	{
		export_no_commands(data);
		return ;
	}
	while (temp)
	{
		is_export_var_name_valid(temp);
		temp = temp->next;
	}
	temp = input_head;
	data = data_head;
	execute_export_commands(data, temp);
	temp = input_head;
	data = data_head;
	data->env_list = env_head;
	//ft_export_type_printer(temp);
	ft_printf("export finished\n");
}
