/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:38:55 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/26 15:53:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_shell_level_value(char *env_var_value)
{
	int	i;

	i = 0;
	while (env_var_value[i] != '\0')
	{
		if (ft_isdigit(env_var_value[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	set_new_node_data(t_env_list *node, char *new_value)
{
	char	*new_string;

	free(node->env_var_value);
	node->env_var_value = new_value;
	new_string = ft_strjoin(node->env_var_name, "=");
	if (new_string == NULL)
		return (NO_MEMORY);
	free(node->env_var);
	node->env_var = ft_strjoin(new_string, new_value);
	free(new_string);
	if (node->env_var == NULL)
		return (NO_MEMORY);
	return (SUCCESS);
}

int	update_shell_level(t_shelldata *data)
{
	t_env_list	*temp;
	int			shell_level;
	int			i;
	char		*temp_string;

	temp = data->env_list;

	while (temp != NULL && ft_strcmp(temp->env_var_name, "SHLVL") != 0)
		temp = temp->next;
	if (temp == NULL)
		return (NO_ERROR);
	i = 0;
	shell_level = check_shell_level_value(temp->env_var_value);
	if (shell_level == 1)
		shell_level = ft_atoi(temp->env_var_value);
	temp_string = ft_itoa(shell_level + 1);
	if (temp_string == NULL)
		return (NO_MEMORY);
	if (set_new_node_data(temp, temp_string) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
