/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/30 14:11:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* For the readline functions*/
# include <readline/readline.h>
# include <readline/history.h>

/* For many such as fork, pipe, access, etc.*/
# include <unistd.h>

/* For malloc, free, exit, etc.*/
# include <stdlib.h>

/* For the Open function*/
# include <fcntl.h>

/*For the signal functions*/
# include <signal.h>

/*libft functions*/
# include "libft/libft.h"

enum e_parse_data
{
	PIPE = 1,
	INPUT_REDIRECTION = 2,
	OUTPUT_REDIRECTION = 4,
	APPENDING_OUTPUT = 8
};

enum e_exit_values
{
	SUCCESS = 0,
	FAILURE = 1
};

enum e_errors
{
	NO_ERROR = 0,
	NO_COMMAND = 1,
	NO_FILE = 2,
	NO_DIRECTORY = 3,
	NO_PERMISSION = 4,
	NO_ENV = 5,
	NO_MEMORY = 6,
	NO_PIPE = 7,
	NO_FORK = 8,
	NO_QUOTE = 9
};

typedef struct s_parse_data
{
	int	pipes;
	int	input_redirection;
	int	output_redirection;
	int	appending_output;
}	t_parse_data;

typedef struct s_shelldata
{
	char			**env_variables;
	char			*input;
	char			**split_input;
	int				exit_value;
	t_parse_data	parse_data;
}		t_shelldata;

//int	rl_clear_history(void);

#endif