/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:58 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/27 16:37:17 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_unset_var_name_valid(t_input_list *temp)
{
	int	i;

	i = 0;
	if (!ft_isalpha(temp->input[i]) && temp->input[i] != '_')
	{
		ft_printf("bananashell: unset: `%s': not a valid identifier\n", \
		temp->input);
		temp->type = INVALID_UNSET_INPUT;
		return ;
	}
	while (temp->input[i] != '\0' && temp->input[i] != '=')
	{
		if (ft_isalnum(temp->input[i]) || temp->input[i] == '_')
			i++;
		else
		{
			ft_printf("bananashell: unset: `%s': not a valid identifier\n", \
			temp->input);
			temp->type = INVALID_UNSET_INPUT;
			return ;
		}
	}
	temp->type = VALID_UNSET_INPUT;
	ft_printf("unset input was valid\n");
}

static int	check_if_unset_env_exists(t_shelldata *data, t_input_list *temp)
{
	ft_printf("got into the check_if_env_exists\n");
	while (data->env_list)
	{
		if (!ft_strncmp(data->env_list->env_var_name, temp->input, \
		ft_strlen(data->env_list->env_var_name)))
		{
			ft_printf("env found\n");
			return (1);
		}
		data->env_list = data->env_list->next;
	}
	return (0);
}

int	check_if_first_node(t_shelldata *data, char *specifier)
{
	t_env_list	*next;

	next = data->env_list->next;
	//if (!ft_strcmp(data->env_list->env_var_name, specifier))
	if (!ft_strncmp(data->env_list->env_var_name, specifier, \
	ft_strlen(specifier) + 1))
	{
		free(data->env_list->env_var_name);
		free(data->env_list->env_var_value);
		free(data->env_list->env_var);
		free(data->env_list);
		data->env_list = NULL;
		data->env_list = next;
		return (YES);
	}
	return (NO);
}

void	remove_from_env_list(t_shelldata *data, char *specifier)
{
	t_env_list	*temp;
	t_env_list	*temp2;

	temp = data->env_list;
	if (check_if_first_node(data, specifier) == YES)
		return ;
	while (temp->next != NULL)
	{
		if (!ft_strncmp(temp->next->env_var_name, specifier, \
		ft_strlen(specifier) + 1))
		{
			temp2 = temp->next->next;
			temp->next = temp2;
			free(temp->next->env_var_name);
			free(temp->next->env_var_value);
			free(temp->next->env_var);
			free(data->env_list);
			data->env_list = NULL;
			return ;
		}
		temp = temp->next;
	}
}

static void	execute_unset_commands(t_shelldata *data, t_input_list *temp)
{
	while (temp)
	{
		if (temp->type == VALID_UNSET_INPUT)
		{
			if (check_if_unset_env_exists(data, temp) == 1)
			{
				ft_printf("env exists, we should remove it\n");
				remove_from_env_list(data, temp->input);
			}
			else
			{
				ft_printf("env does not exist, do nothing\n");
			}
		}
		temp = temp->next;
	}
}

void	my_unset(t_shelldata *data, t_input_list *temp)
{
	t_input_list	*input_head;
	t_env_list		*env_head;
	t_shelldata		*data_head;

	input_head = temp;
	data_head = data;
	env_head = data->env_list;
	if (!temp->next)
		return ;
	temp = temp->next;
	while (temp)
	{
		is_unset_var_name_valid(temp);
		temp = temp->next;
	}
	temp = input_head;
	data = data_head;
	execute_unset_commands(data, temp);
	//create_2d_env(data);
	temp = input_head;
	data = data_head;
	data->env_list = env_head;
	ft_printf("unset finished\n");
}
