/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 23:52:53 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/07 23:53:08 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	child_handling(t_shelldata *data)
{
	int	error;
	//We need to do proper error handling here.
	error = child_pre_check(data);
	error = create_exit_value_env(data);
	if (error != SUCCESS)
		exit(1);
}
