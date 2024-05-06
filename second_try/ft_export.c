/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:01 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 11:02:56 by tvalimak         ###   ########.fr       */
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

/*This one checks if the export command is formatted properly*/
/*
static void	print_env_list(t_shelldata *data)
{
	t_env_list		*temp;

	temp = data->env_list;
	while (temp)
	{
		printf("%s\n", temp->env_var_name);
		printf("%s\n", temp->env_var_value);
		printf("%s\n", temp->env_var);
		printf("---------------------------------------------\n");
		temp = temp->next;
	}
}*/

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
	ft_printf("export input was valid\n");
}

static void export_sorted_list(t_env_list *temp_list)
{
	t_env_list		*temp;
	t_env_list		*temp2;
	char			*temp_env;

	temp = temp_list;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strcmp(temp->env_var_name, temp2->env_var_name) > 0)
			{
				temp_env = temp->env_var;
				temp->env_var = temp2->env_var;
				temp2->env_var = temp_env;
				temp_env = temp->env_var_name;
				temp->env_var_name = temp2->env_var_name;
				temp2->env_var_name = temp_env;
				temp_env = temp->env_var_value;
				temp->env_var_value = temp2->env_var_value;
				temp2->env_var_value = temp_env;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

static void	export_no_commands(t_shelldata *data)
{
	t_env_list		*temp;

	temp = data->env_list;
	if (!temp)
		return ;
	while (temp)
	{
		if (temp->env_var_name[0] != '?')
		{
			if (temp->env_var_value != NULL)
			{
				ft_printf("declare -x %s=\"%s\"\n", temp->env_var_name, \
				temp->env_var_value);
			}
			else
				ft_printf("declare -x %s\n", temp->env_var_name);
		}
		temp = temp->next;
	}
	ft_printf("export without commands finished\n");
}

// if (!ft_strcmp(temp_env->env_var_name, temp->input))
// we need to compare the input string until char = against the temp_env->env_var_name
/*This one goes through the env list and sees if the new env var
  already exists*/
static int	check_if_export_env_exists(t_shelldata *data, t_input_list *temp)
{
	int i;
	t_env_list	*temp_env;

	i = 0;
	while (temp->input[i] != '=')
		i++;
	temp_env = data->env_list;
	ft_printf("got into the check_if_env_exists\n");
	while (temp_env)
	{
		if (!ft_strncmp(temp->input, temp_env->env_var_name, i))
		{
			ft_printf("env found\n");
			return (1);
		}
		temp_env = temp_env->next;
	}
	ft_printf("env not found\n");
	return (0);
}

static int	add_new_env_var(t_shelldata *data, t_input_list *temp, int i, int flag)
{
	t_env_list	*new_env;
	t_env_list	*temp_env;

	while (temp->input[i] != '=')
		i++;
	new_env = ft_calloc(1, sizeof(t_env_list));
	if (!new_env)
		return (NO_MEMORY);
	new_env->env_var_name = ft_substr(temp->input, 0, i);
	if (new_env->env_var_name == NULL)
		return (NO_MEMORY);
	if (flag == 1)
	{
		new_env->env_var_value = ft_substr(temp->input, i + 1,
				ft_strlen(temp->input) - i - 1);
		if (new_env->env_var_value == NULL)
			return (NO_MEMORY);
		new_env->env_var = ft_strdup(temp->input);
		if (new_env->env_var == NULL)
			return (NO_MEMORY);
	}
	new_env->next = NULL;
	temp_env = data->env_list;
	while (temp_env->next)
		temp_env = temp_env->next;
	temp_env->next = new_env;
	return (SUCCESS);
	ft_printf("new env var added\n");
}

/*This function replaces the env var value if it already exists*/
static int	replace_env_var(t_shelldata *data, t_input_list *temp, int i, int flag)
{
	t_env_list	*temp_env;

	temp_env = data->env_list;
	while (temp_env)
	{
		if (!ft_strncmp(temp_env->env_var_name, temp->input, \
		ft_strlen(temp_env->env_var_name)))
		{
			if (flag == 1)
			{
				while (temp->input[i] != '=')
					i++;
				temp_env->env_var_value = ft_substr(temp->input, i + 1, \
				ft_strlen(temp->input) - i - 1);
				if (temp_env->env_var_value == NULL)
					return (NO_MEMORY);
				ft_printf("env var replaced\n");
				return (SUCCESS);
			}
			else
				temp_env->env_var_value = "";
		}
		temp_env = temp_env->next;
	}
	return (SUCCESS);
}
/*  This function will go through the input list and figures out do we
    replace or add the new key/value pair */
static int	execute_export_commands(t_shelldata *data, t_input_list *temp)
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
					return (replace_env_var(data, temp, 0, 1));
				else
					return (add_new_env_var(data, temp, 0, 1));
			}
			else
			{
				if (check_if_export_env_exists(data, temp) == 1)
					return (SUCCESS);
				else
					return (add_new_env_var(data, temp, 0, 0));
			}
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

/* my_export main function*/
int	ft_export(t_shelldata *data)
{
	t_input_list	*temp;

	temp = data->input_list;
	if (temp->next == NULL)
	{
		export_sorted_list(data->env_list);
		export_no_commands(data);
		//print_env_list(data);
		return (SUCCESS);
	}
	temp = temp->next;
	while (temp)
	{
		is_export_var_name_valid(temp);
		temp = temp->next;
	}
	temp = data->input_list;
	execute_export_commands(data, temp);
	create_2d_env(data);
	ft_printf("export finished\n");
	//print_env_list(data);
	return (SUCCESS);
}