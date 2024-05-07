/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner_helper_funcs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:18:26 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/07 11:54:25 by tvalimak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_up_string_data(t_new_string_data *data, t_input_list *temp,
	t_shelldata *shell_data, char *new_string)
{
	data->i = 0;
	data->j = 0;
	data->quote = 'a';
	data->temp = temp;
	data->env = shell_data->env_list;
	data->new_string = new_string;
	data->shell_data = shell_data;
}
