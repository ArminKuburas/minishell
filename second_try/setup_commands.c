/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 09:35:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/24 09:56:54 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_command(const char *builtin, char *command)
{
	if (ft_strlen(builtin) != ft_strlen(command))
		return (0);
	if (ft_strcmp(builtin, command) == 0)
		return (1);
	return (0);
}



/*This function first tries to see if a command exists
If one does exist it tries to check if its perhaps a builtin
If it isn't we will then try to find it. First we try as is
Since it might have the path already there. Otherwise we try
To use the PATH env variable. We handle errors as needed.*/
int	setup_command(t_shelldata *data, int index)
{
	t_input_list	*temp;
	int				i;
	int				error;

	temp = data->input_list;
	i = index;
	while (i > 0)
	{
		while (temp->type != PIPE)
			temp = temp->next;
		temp = temp->next;
		i--;
	}
	while (temp && temp->type != PIPE)
	{
		if (temp->type == COMMAND)
		{
			error = is_it_builtin(temp->input, &data->child_data[index]);
			if (error == NOT_FOUND)
				error = is_it_command(temp->input, data, index);
			return (error);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}
