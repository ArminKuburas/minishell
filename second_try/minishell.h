/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/16 19:47:14 by akuburas         ###   ########.fr       */
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

/*For boolean type*/
# include <stdbool.h>

/*Definition for SIGINT*/
# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT


typedef enum e_state
{
	DEFAULT,
	HEREDOC,
	HANDLER
}	t_state;

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
	REDIRECT_INPUT = 42,
	INPUT_FILE = 43,
	REDIRECT_HEREDOC = 44,
	HEREDOC_FILE = 45,
	REDIRECT_OUTPUT = 52,
	OUTPUT_FILE = 53,
	REDIRECT_APPEND = 54,
	APPEND_FILE = 55,
	COMMAND = 62,
	COMMAND_ARGUMENT = 63,
	PIPE = 72,
	POTENTIAL_SPLIT = 82,
	WORD_SPLIT = 83
};

enum e_yes_no
{
	NO = 0,
	YES = 1
};

typedef struct s_input_list
{
	int					type;
	int					word_split;
	bool				needs_cleaning;
	char				*input;
	char				*old_input;
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
	t_parse_data	child_data;
	char			**env_variables;
	char			*input;
	int				exit_value;
}		t_shelldata;

//A required struct for the functions that create new strings
typedef struct s_new_string_data
{
	int				i;
	int				j;
	char			quote;
	char			*new_string;
	t_input_list	*temp;
	t_env_list		*env;
}	t_new_string_data;

//readline functions

//int			rl_clear_history(void);
//void		rl_replace_line(char *str, int num);

//data_parser functions

int			count_words(char *input, int *word_count);
int			mini_split(char *input, t_shelldata *data);
int			parse_split_input(t_shelldata *data);
int			parser_quote_found(char *input, int *i, int len);

//input_list functions
void		add_input_list(t_input_list *input_list, t_input_list *new_node);
int			clear_input(t_input_list *input_list, int error);
int			create_input(char *input, int len, t_input_list *input_list);
void		input_type_assigner(t_input_list *input_list);
int			strlen_last_input(t_input_list *input_list);

//env_list functions
int			duplicate_env(char **env, t_shelldata *data);
int			clear_env_list(t_env_list *env_list, int error);
int			env_str_cmpr(char *env, char *str, int len);

//data_cleaner functions
int			new_length(t_input_list *temp, t_env_list *env);
int			split_cleaner(t_shelldata *data);
void		copy_dollar(t_new_string_data *data);
t_env_list	*try_to_find_env(t_env_list *env, char *str, int len);
void		potential_split_create(t_new_string_data *data);

// static void	signal_handler(int signal);

#endif