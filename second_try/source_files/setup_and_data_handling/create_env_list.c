/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:29:51 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/06 14:18:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	create_2d_env(t_shelldata *data)
{
	int			i;
	int			j;
	t_env_list	*temp;

	if (data->env_variables != NULL)
		free(data->env_variables);
	i = 0;
	temp = data->env_list;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	data->env_variables = ft_calloc(i + 1, sizeof(char *));
	if (data->env_variables == NULL)
		return (NO_MEMORY);
	j = 0;
	temp = data->env_list;
	while (j < i)
	{
		data->env_variables[j] = temp->env_var;
		j++;
		temp = temp->next;
	}
	return (SUCCESS);
}

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
			return (NO_MEMORY);
		if (simplify_env_data(env_list) != SUCCESS)
			return (NO_MEMORY);
	}
	else
	{
		new = ft_calloc(1, sizeof(t_env_list));
		if (new == NULL)
			return (NO_MEMORY);
		env_list->next = new;
		new->env_var = ft_strdup(env);
		if (new->env_var == NULL)
			return (NO_MEMORY);
		if (simplify_env_data(new) != SUCCESS)
			return (NO_MEMORY);
	}
	return (SUCCESS);
}
/*
static int	get_env_list_size(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	not_on_the_list(char *var, t_env_list *temp)
{
	if (!temp->env_var)
		return (0);
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->env_var, ft_strlen(var)) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static char	*find_top_item(char **env, t_env_list *temp)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (not_on_the_list(env[i], temp) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

int	duplicate_env(char **env, t_shelldata *data)
{
	int			i;
	int			j;
	int			env_size;
	char		*top;
	t_env_list	*temp;

	i = 0;
	data->env_list = ft_calloc(1, sizeof(t_env_list));
	if (data->env_list == NULL)
		return (FAILURE);
	env_size = get_env_list_size(env);
	temp = data->env_list;
	while (i < env_size)
	{
		j = 1;
		top = env[0];
		if (not_on_the_list(top, temp) == 1)
			top = find_top_item(env, temp);
		while (j < env_size)
		{
			if (ft_strncmp(top, env[j], ft_strlen(top)) > 0
				&& not_on_the_list(env[j], temp) == 0)
				top = env[j];
			j++;
		}
		if (create_env(top, temp) != SUCCESS)
			return (clear_env_list(data->env_list, NO_MEMORY));
		if (temp->next != NULL)
			temp = temp->next;
		i++;
	}
	temp = data->env_list;
	return (SUCCESS);
}*/

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
			return (clear_env_list(data->env_list, NO_MEMORY));
		if (temp->next != NULL)
			temp = temp->next;
		i++;
	}
	if (create_2d_env(data) != SUCCESS)
		return (clear_env_list(data->env_list, NO_MEMORY));
	return (SUCCESS);
}
