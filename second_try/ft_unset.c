/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:58 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/06 13:55:08 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unset_var_name_valid(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '_' || !ft_isalpha(input[i]))
	{
		ft_printf("1\n");
		ft_putstr_fd("bananashell: unset: `", STDERR_FILENO);
		ft_putstr_fd(input, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (FAILURE);
	}
	while (input[i] != '\0' && input[i] != '=')
	{
		if (input[i] == '_' || ft_isalpha(input[i]))
			i++;
		else
		{
			ft_printf("2\n");
			ft_putstr_fd("bananashell: unset: `", STDERR_FILENO);
			ft_putstr_fd(input, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

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
/* my_unset main function*/
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
