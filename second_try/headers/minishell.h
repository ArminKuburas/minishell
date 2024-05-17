/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:16:05 by akuburas          #+#    #+#             */
/*   Updated: 2024/05/17 14:27:50 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*For errno global variable*/
# include <errno.h>

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
# include "../libft/libft.h"

/*For boolean type*/
# include <stdbool.h>

/*For the waitpid function*/
# include <sys/wait.h>

/*For the tcgetattr and tcsetattr functions*/
# include <termios.h>

/*For the overflow checks*/
# include <limits.h>

/*Global variable*/
extern int	g_exit_value;

# define RED	"\001\x1b[31m\002"
# define GREEN	"\001\x1b[32m\002"
# define YELLOW	"\001\x1b[33m\002"
# define RESET	"\001\x1b[0m\002"
# define BANANA_EMOJI "\001\xF0\x9F\x8D\x8C\002"

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
	NO_DUP = 10,
	NO_EXECVE = 11,
	NOT_FOUND = 12,
	EXECUTION_FORBIDDEN = 13,
	IS_DIRECTORY = 14,
	FOUND = 15
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
	pid_t	pid;
	int		p_fd_in[2];
	int		p_fd_out[2];
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
	char			*pwd;
	char			*old_pwd;
	int				cd_used;
	char			*input;
	int				exit_value;
}		t_shelldata;

//A required struct for the functions that create new strings
typedef struct s_new_string_data
{
	int				i;
	int				j;
	int				exit_value;
	char			quote;
	char			*new_string;
	t_input_list	*temp;
	t_env_list		*env;
	t_shelldata		*shell_data;
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

//get next line functions
char		*get_next_line(int fd);


//readline functions
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
void		remove_from_env_list(t_shelldata *data, char *specifier);

//data_cleaner functions
int			new_length(t_input_list *temp, t_env_list *env);
int			split_cleaner(t_shelldata *data);
void		copy_dollar(t_new_string_data *data);
t_env_list	*try_to_find_env(t_env_list *env, char *str, int len);
void		potential_split_create(t_new_string_data *data);
void		split_env(t_new_string_data *data, t_env_list	*temp_env);
void		set_up_string_data(t_new_string_data *data, t_input_list *temp,
				t_shelldata *shell_data, char *new_string);

//new mini split functions
int			new_mini_split(t_shelldata *data);
int			duplicate_input(char *input, t_shelldata *data, int *i);

//signal handler
void		sigint_handler(int sig);
void		heredoc_handler(int sig);
void		parent_signals(void);
void		heredoc_signals(void);
void		standby_signals(void);
void		handler_signals(void);
void		caret_switch(int on);
void		signals_off(void);
void		child_signals(void);
void		child_sigint_handler(int sig);
void		parent_sigquit(int sig);

//built_in functions
int			ft_cd(t_shelldata *data, char **inputs);
int			ft_env(t_shelldata *data, int fd);
int			ft_export(t_shelldata *data, char **inputs, int fd);
int			ft_exit(t_shelldata *data, char **inputs);
int			ft_unset(t_shelldata *data, char **inputs);
int			ft_echo(t_child_data *data, int fd);
int			ft_pwd(char *pwd, int fd);
int			child_pre_check(t_shelldata *data);
char		*ret_env(t_shelldata *data, char *var);
void		update_env_pwd(t_shelldata *data);
int			refresh_pwd(t_shelldata *data);
void		refresh_old_pwd(t_shelldata *data);
int			replace_env_var(t_shelldata *data, char *input, int i, int flag);
int			add_new_env_var(t_shelldata *data, char *input, int i, int flag);
void		export_sorted_list(t_env_list *env_list);
void		export_no_commands(t_shelldata *data, int fd);
void		swap_env_vars(t_env_list *temp, t_env_list *temp2);
void		check_format(t_shelldata *data, char **inputs);
void		clean_exit(t_shelldata *data, int flag);
int			is_unset_var_name_valid(char *input);

//heredoc
void		heredoc(t_shelldata data, t_input_list *temp);

//child processing functions
int			set_up_child_data(t_shelldata *data);
void		setup_redirects(t_shelldata *data, int index);
int			setup_command(t_shelldata *data, int index);
int			is_it_command(char *input, t_shelldata *data, int index);
void		free_child_data(t_child_data *data);
int			setup_pipes(t_shelldata *data, int amount);
void		set_all_error(t_shelldata *data);
void		child_failed(t_shelldata *data, int error);
void		command_error_message(int error, t_shelldata *data, int amount);
int			create_command_arguments(t_child_data *child, t_input_list *start);
void		try_access(char *path, int *error);
int			create_variables(char ***path_variables, t_env_list *env_list);
void		ambiguous_redirect(t_shelldata *data, int i, t_input_list *input);
void		handle_heredoc(t_shelldata *data, int i, t_input_list *input);
char		*modify_input(char *input, t_env_list *env_list);
int			no_env_found(char *new_input, int *j);
void		handle_output_error(t_shelldata *data, int i, t_input_list *input);

//execute_children functions
int			execute_commands(t_shelldata *data);
void		clean_everything_up(t_shelldata *data, int exit_value);
void		execve_failed_cleanup(t_shelldata *data, t_child_data *child_data);
void		clean_other_children(t_shelldata *data, int i);
int			check_child_pipes(t_child_data *child_data);
int			use_builtin(t_child_data *child_data, int fd, t_shelldata *data);
void		wait_for_children(t_shelldata *data);
int			execute_child(t_shelldata *data, t_child_data *child_data, int i);
void		child_handler(t_shelldata *data, t_child_data *child_data, int i);
void		fork_failed(t_shelldata *data, int amount);
void		close_other_fds(t_shelldata *data, int j, int i);

//executioner
int			execute_built_ins(t_shelldata *data, t_input_list *temp);
//error functions
int			check_pipes(t_shelldata *data);
void		split_memory_failed(t_shelldata *data);

//main helpers
int			new_env_node(t_env_list *old_node, char *env_name, char *env_value);
int			create_question_node(t_shelldata *data, t_env_list *temp);
int			create_exit_value_env(t_shelldata *data);
int			initial_env_creation(char **env, t_shelldata *data);
int			initial_setup(t_shelldata *data, int argc, char **argv, char **env);
int			check_argc_argv(int argc, char **argv);
void		child_handling(t_shelldata *data);

//Testers
void	*fake_ft_calloc(int amount, int size);
int		fake_open(void);
int		fake_fork(void);
int		fake_dup2(void);

int			check_shell_level_value(char *env_var_value);

//error messages
void		num_fail(t_shelldata *data, char *input);

#endif