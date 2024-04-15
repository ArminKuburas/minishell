/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:10:36 by tvalimak          #+#    #+#             */
/*   Updated: 2024/04/15 19:37:38 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_pwd(t_shelldata data, t_input_list *temp)
{
	(void)data;
	(void)temp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_printf("ERROR IN PWD\n");
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}
