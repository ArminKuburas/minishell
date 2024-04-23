/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:08:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/23 12:08:06 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  this function attempts to redirect input from a file
It first confirms if it can access and open the given input_file.
It not it sets the correct exit_value (error value)*/
void	handle_redirect_input(t_child_data *data, t_input_list *input)
{
	if (data->exit_value != 0)
		return ;
	if (data->fd_in != 0)
		close(data->fd_in);
	data->fd_in = open(input->input, O_RDONLY, 0777);
	if (data->fd_in == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->exit_value = 1;
	}
	else if (data->fd_in == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_value = 1;
	}
}

void	handle_redirect_output(t_child_data *data, t_input_list *input)
{
	if (data->exit_value != 0)
		return ;
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = open(input->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->exit_value = 1;
	}
	else if (data->fd_out == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_value = 1;
	}
}

void	handle_redirect_append(t_child_data *data, t_input_list *input)
{
	if (data->exit_value != 0)
		return ;
	if (data->fd_out != 1)
		close(data->fd_out);
	data->fd_out = open(input->input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out == -1 && !access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->exit_value = 1;
	}
	else if (data->fd_out == -1 && access(input->input, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->input, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_value = 1;
	}
}

void	setup_redirects(t_shelldata *data, int index)
{
	t_input_list	*temp;
	int				i;

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
		if (temp->type == REDIRECT_INPUT)
			handle_redirect_input(&data->child_data[index], temp->next);
		if (temp->type == REDIRECT_OUTPUT)
			handle_redirect_output(&data->child_data[index], temp->next);
		if (temp->type == REDIRECT_APPEND)
			handle_redirect_append(&data->child_data[index], temp->next);
		temp = temp->next;
	}
}
