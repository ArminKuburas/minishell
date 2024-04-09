/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/09 10:49:43 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* For the readline functions*/
# include <readline/history.h>
# include <readline/readline.h>

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

/*Definition for SIGINT*/
# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT

typedef enum e_state
{
	DEFAULT,
	HEREDOC,
	HANDLER
}	t_state;

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
	FAILURE = 1,
	UNKNOWN = 2
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

enum e_child_status
{
	NO_PIPE_AVAILABLE,
	OUTPUT_PIPE,
	INPUT_PIPE,
	OP_IP,
	NO_REDIRECTION,
	OUTPUT_REDIRECT,
	INPUT_REDIRECT,
	OR_IR
};

typedef struct s_child_data
{
	int		pipe_situation;
	int		p_fd_1[2];
	int		p_fd_2[2];
	int		redirections;
	int		fd_in;
	int		fd_out;
	char	**env;
	char	*command;
	char	**command_inputs;
}	t_child_data;

enum e_input_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	COMMAND,
	COMMAND_INPUT,
	PIPE,
	WORD_SPLIT
};

typedef struct s_input_list
{
	int					type;
	int					word_split;
	char				*input;
	struct s_input_list	*next;
	struct s_input_list	*prev;
}	t_input_list;

typedef struct s_env_list
{
	char				*env_var_name;
	char				*env_var_value;
	char				*env_var;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_parse_data
{
	int				processes;
	t_child_data	*child_data;
}	t_parse_data;

typedef struct s_shelldata
{
	t_env_list		*env_list;
	t_input_list	*input_list;
	char			**env_variables;
	char			*input;
	int				exit_value;
}		t_shelldata;

//readline functions

int			rl_clear_history(void);
void		rl_replace_line(char *str, int num);

int			mini_split(char *input, t_shelldata *data);
void		free_double_array(char ***array);
// static void	signal_handler(int signal);
int			parse_split_input(t_shelldata *data);
int			split_cleaner(t_shelldata *data);

#endif