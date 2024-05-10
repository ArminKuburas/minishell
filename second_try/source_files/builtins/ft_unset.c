/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:58 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/09 10:58:22 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	check_if_unset_env_exists(t_shelldata *data, char *input)
{
	t_env_list	*temp2;

	temp2 = data->env_list;
	while (temp2)
	{
		if (!ft_strncmp(temp2->env_var_name, input, \
		ft_strlen(temp2->env_var_name)))
			return (YES);
		temp2 = temp2->next;
	}
	return (NO);
}

int	check_if_first_node(t_shelldata *data, char *specifier)
{
	t_env_list	*next;

	if (!ft_strcmp(data->env_list->env_var_name, specifier))
	{
		free(data->env_list->env_var_name);
		free(data->env_list->env_var_value);
		free(data->env_list->env_var);
		next = data->env_list->next;
		free(data->env_list);
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
		if (!ft_strcmp(temp->next->env_var_name, specifier))
		{
			free(temp->next->env_var_name);
			free(temp->next->env_var_value);
			free(temp->next->env_var);
			temp2 = temp->next->next;
			free(temp->next);
			temp->next = temp2;
			return ;
		}
		temp = temp->next;
	}
}

static int	execute_unset_commands(t_shelldata *data, char *input)
{
	if (check_if_unset_env_exists(data, input) == YES)
	{
		remove_from_env_list(data, input);
		return (SUCCESS);
	}
	else
		return (SUCCESS);
}

int	ft_unset(t_shelldata *data, char **inputs)
{
	int	i;
	int	return_value;

	i = 1;
	return_value = SUCCESS;
	if (inputs[i] == NULL)
		return (SUCCESS);
	while (inputs[i] != NULL)
	{
		if (is_unset_var_name_valid(inputs[i]) == SUCCESS)
			execute_unset_commands(data, inputs[i]);
		else
			return_value = FAILURE;
		i++;
	}
	create_2d_env(data);
	return (return_value);
}
