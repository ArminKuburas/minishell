/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:05:58 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/19 16:18:34 by tvalimak         ###   ########.fr       */
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
		temp->type = INVALID_EXPORT_INPUT;
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
			temp->type = INVALID_EXPORT_INPUT;
			return ;
		}
	}
	temp->type = VALID_EXPORT_INPUT;
}

static int	check_if_unset_env_exists(t_shelldata data, t_input_list *temp)
{
	ft_printf("got into the check_if_env_exists\n");
	while (data.env_list)
	{
		if (!ft_strncmp(data.env_list->env_var_name, temp->input, \
		ft_strlen(data.env_list->env_var_name)))
		{
			ft_printf("env found\n");
			return (1);
		}
		data.env_list = data.env_list->next;
	}
	return (0);
}

static void	execute_unset_commands(t_shelldata data, t_input_list *temp)
{
	while (temp)
	{
		if (temp->type == VALID_UNSET_INPUT)
		{
			if (check_if_unset_env_exists(data, temp) == 1)
			{
				ft_printf("env exists, we should remove it\n");
				break ;
			}
			else
			{
				ft_printf("env does not exist, do nothing\n");
				break ;
			}
		}
		temp = temp->next;
	}
}

void	my_unset(t_shelldata data, t_input_list *temp)
{
	t_input_list	*input_head;
	t_shelldata		*data_head;

	input_head = temp;
	data_head = &data;
	if (!temp->next)
		return ;
	while (temp)
	{
		is_unset_var_name_valid(temp);
		temp = temp->next;
	}
	temp = input_head;
	data = *data_head;
	execute_unset_commands(data, temp);
	ft_printf("unset finished\n");
}
