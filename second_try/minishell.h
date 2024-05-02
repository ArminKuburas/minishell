/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/02 09:09:59 by tvalimak         ###   ########.fr       */
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

/*For the waitpid function*/
# include <sys/wait.h>

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
	NO_QUOTE = 9,
	NOT_FOUND = 10,
	EXECUTION_FORBIDDEN = 11,
	IS_DIRECTORY = 12,
	FOUND = 13
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
	int		p_fd_in[2];
	int		p_fd_out[2];
	int		redirections;
	int		fd_in;
	int		fd_out;
	char	**env;
	char	*command;
	char	**command_inputs;
	int		exit_value;
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
	WORD_SPLIT = 83,
	BUILTIN = 92
};

enum e_export_input_type
{
	INVALID_EXPORT_INPUT = 84,
	VALID_EXPORT_INPUT = 85,
	VALID_EXPORT_COMMAND = 86,
	INVALID_UNSET_INPUT = 87,
	VALID_UNSET_INPUT = 88,
	VALID_UNSET_COMMAND = 89,
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

typedef struct s_shelldata
{
	t_env_list		*env_list;
	t_input_list	*input_list;
	t_child_data	*child_data;
	int				command_amount;
	char			**env_variables;
	char			*pwd; // subject for change
	char			*old_pwd; // subject for change
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

//A struct for the mini_split

typedef struct s_split_data
{
	int				i;
	int				len;
	int				word_count;
	char			quote;
	char			*input;
	t_input_list	*node_one;
}	t_split_data;
//readline functions

typedef void	(*t_handler)(int);

int			rl_clear_history(void);
void		rl_replace_line(char *str, int num);

//data_parser functions

int			count_words(t_split_data *split_data);
int			mini_split(char *input, t_shelldata *data);
int			parse_split_input(t_shelldata *data);
int			parser_quote_found(t_split_data *data);

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
int			update_shell_level(t_shelldata *data);
int			create_2d_env(t_shelldata *data);


//data_cleaner functions
int			new_length(t_input_list *temp, t_env_list *env);
int			split_cleaner(t_shelldata *data);
void		copy_dollar(t_new_string_data *data);
t_env_list	*try_to_find_env(t_env_list *env, char *str, int len);
void		potential_split_create(t_new_string_data *data);

int			new_mini_split(t_shelldata *data);


//signal handler

void		sigint_handler(int sig);
void		heredoc_handler(int sig);
void		signal_handler(int signal, t_handler handler);
void		parent_signals(void);
void		heredoc_signals(void);
void		standby_signals(void);
void		handler_signals(void);
void		caret_switch(int on);

//built_in functions
void		my_echo(t_input_list *temp);
void		my_cd(t_shelldata *data, t_input_list *temp);
void		my_pwd(t_shelldata *data, t_input_list *temp);
void		my_export(t_shelldata *data, t_input_list *temp);
void		my_unset(t_shelldata *data, t_input_list *temp);
void		my_exit(t_shelldata *data, t_input_list *temp);

//execute functions
void		my_env(t_shelldata *data);

//heredoc
void		heredoc(t_shelldata data, t_input_list *temp);

//child processing functions
int			set_up_child_data(t_shelldata *data);
void		setup_redirects(t_shelldata *data, int index);
int			setup_command(t_shelldata *data, int index);
int			is_it_command(char *input, t_shelldata *data, int index);
void		free_child_data(t_child_data *data);
int			setup_pipes(t_shelldata *data, int amount);

//executioner
int			execute_built_ins(t_shelldata *data, t_input_list *temp);

#endif