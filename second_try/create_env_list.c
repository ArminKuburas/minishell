/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:29:51 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/11 12:50:28 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clear_env_list(t_env_list *env_list, int error)
{
	t_env_list	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if (temp->env_var_name != NULL)
			free(temp->env_var_name);
		temp->env_var_name = NULL;
		if (temp->env_var_value != NULL)
			free(temp->env_var_value);
		temp->env_var_value = NULL;
		if (temp->env_var != NULL)
			free(temp->env_var);
		temp->env_var = NULL;
		temp = temp->next;
		free(env_list);
		env_list = temp;
	}
	if (error == NO_MEMORY)
		ft_putstr_fd("Error: No memory\n", 2);
	return (error);
}

int	simplify_env_data(t_env_list *env_list)
{
	int	i;

	i = 0;
	while (env_list->env_var[i] != '=')
		i++;
	env_list->env_var_name = ft_substr(env_list->env_var, 0, i);
	if (env_list->env_var_name == NULL)
		return (NO_MEMORY);
	env_list->env_var_value = ft_substr(env_list->env_var, i + 1,
			ft_strlen(env_list->env_var) - i - 1);
	if (env_list->env_var_value == NULL)
		return (NO_MEMORY);
	return (SUCCESS);
}

int	create_env(char *env, t_env_list *env_list)
{
	t_env_list	*new;

	if (env_list->env_var == NULL)
	{
		env_list->env_var = ft_strdup(env);
		if (env_list->env_var == NULL)
			return (clear_env_list(env_list, NO_MEMORY));
		if (simplify_env_data(env_list) != SUCCESS)
			return (clear_env_list(env_list, NO_MEMORY));
	}
	else
	{
		new = ft_calloc(1, sizeof(t_env_list));
		if (new == NULL)
			return (clear_env_list(env_list, NO_MEMORY));
		env_list->next = new;
		new->env_var = ft_strdup(env);
		if (new->env_var == NULL)
			return (clear_env_list(env_list, NO_MEMORY));
		if (simplify_env_data(new) != SUCCESS)
			return (clear_env_list(env_list, NO_MEMORY));
	}
	return (SUCCESS);
}

int	duplicate_env(char **env, t_shelldata *data)
{
	int			i;
	t_env_list	*temp;

	i = 0;
	data->env_list = ft_calloc(1, sizeof(t_env_list));
	if (data->env_list == NULL)
		return (FAILURE);
	temp = data->env_list;
	while (env[i] != NULL)
	{
		if (create_env(env[i], temp) != SUCCESS)
			return (FAILURE);
		if (temp->next != NULL)
			temp = temp->next;
		i++;
	}
	return (SUCCESS);
}
