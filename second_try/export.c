/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:30:01 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/15 23:06:33 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function should parse the export arguments into env_var_name and value pairs*/

static char	*export_parser(t_shelldata data, t_input_list *temp)
{
	(void)data;
	(void)temp;
	int i;

	i = 0;
	while (temp->input[i] != '\0')
	{
		while (temp->input[i] != '=')
		{
			if (temp->input[i] == '=' && temp->input[i + 1] != '\0')
				return (NULL);
			i++;
		}
	}
	ft_printf("export_parser\n");
}

void	my_export(t_shelldata data, t_input_list *temp)
{
	char *env_name;
	
	if (env_name = export_parser(data, temp) == NULL)
	{
		ft_printf("ERROR IN EXPORT\n");
		return ;
	}
	if (env_name == NULL)
	{
		ft_printf("ERROR IN EXPORT\n");
		return ;
	}


	(void)data;
	(void)temp;
	ft_printf("export\n");
}