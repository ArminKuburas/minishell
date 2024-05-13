/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:34:10 by tvalimak          #+#    #+#             */
/*   Updated: 2024/05/13 12:30:54 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	swap_env_vars(t_env_list *temp, t_env_list *temp2)
{
	char			*temp_env;

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

void	export_sorted_list(t_env_list *env_list)
{
	t_env_list		*temp;
	t_env_list		*temp2;

	temp = env_list;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strcmp(temp->env_var_name, temp2->env_var_name) > 0)
				swap_env_vars(temp, temp2);
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

/*This function replaces the env var value if it already exists*/
int	replace_env_var(t_shelldata *data, char *input, int i, int flag)
{
	t_env_list	*temp_env;

	temp_env = data->env_list;
	while (temp_env)
	{
		if (!ft_strncmp(temp_env->env_var_name, input, \
		ft_strlen(temp_env->env_var_name)))
		{
			if (flag == 1)
			{
				while (input[i] != '=')
					i++;
				temp_env->env_var_value = ft_substr(input, i + 1, \
				ft_strlen(input) - i - 1);
				if (temp_env->env_var_value == NULL)
					return (NO_MEMORY);
				return (SUCCESS);
			}
			else
				temp_env->env_var_value = "";
		}
		temp_env = temp_env->next;
	}
	return (SUCCESS);
}

static int	add_new_env_var_2(t_shelldata *data, t_env_list *new_env, int flag)
{
	t_env_list	*temp_env;

	if (flag == 1)
	{
		new_env->env_var = ft_strdup(new_env->env_var_name);
		new_env->env_var_value = NULL;
	}
	new_env->next = NULL;
	temp_env = data->env_list;
	while (temp_env->next)
		temp_env = temp_env->next;
	temp_env->next = new_env;
	return (SUCCESS);
}

int	add_new_env_var(t_shelldata *data, char *input, int i, int flag)
{
	t_env_list	*new_env;

	while (input[i] != '=' && input[i] != '\0')
		i++;
	new_env = ft_calloc(1, sizeof(t_env_list));
	if (!new_env)
		return (NO_MEMORY);
	new_env->env_var_name = ft_substr(input, 0, i);
	if (new_env->env_var_name == NULL)
		return (NO_MEMORY);
	if (flag == 1)
	{
		new_env->env_var_value = ft_substr(input, i + 1,
				ft_strlen(input) - i - 1);
		if (new_env->env_var_value == NULL)
			return (NO_MEMORY);
		new_env->env_var = ft_strdup(input);
		if (new_env->env_var == NULL)
			return (NO_MEMORY);
	}
	else
		return (add_new_env_var_2(data, new_env, 1));
	return (add_new_env_var_2(data, new_env, 0));
}
