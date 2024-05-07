# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <Tvalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 11:16:12 by akuburas          #+#    #+#              #
#    Updated: 2024/05/07 11:58:17 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
DEBUGFLAGS = -g -Wall -Wextra -Werror
SRCDIR = source_files
BUILTINDIR = $(SRCDIR)/builtins
MAINDIR = $(SRCDIR)/main_signal_and_execution
SETUPDIR = $(SRCDIR)/setup_and_data_handling
SPLITDIR = $(SRCDIR)/split_and_cleaner


MAKE = make bonus
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS =	$(MAINDIR)/main.c \
		$(SETUPDIR)/input_list_functions.c \
		$(SETUPDIR)/create_env_list.c \
		$(SETUPDIR)/type_assigner.c \
		$(SPLITDIR)/split_cleaner.c \
		$(SPLITDIR)/split_cleaner_dollar_functions.c \
		$(SPLITDIR)/cleaner_length_functions.c \
		$(SPLITDIR)/potential_split_functions.c \
		$(SPLITDIR)/new_mini_split.c \
		$(MAINDIR)/signal.c \
		$(BUILTINDIR)/ft_cd.c \
		$(BUILTINDIR)/pwd.c \
		$(BUILTINDIR)/echo.c \
		$(BUILTINDIR)/env.c \
		$(BUILTINDIR)/exit.c \
		$(SETUPDIR)/heredoc.c \
		$(SETUPDIR)/set_up_child_data.c \
		$(SETUPDIR)/setup_commands.c \
		$(SETUPDIR)/setup_helpers.c \
		$(SETUPDIR)/setup_is_it_command.c \
		$(SETUPDIR)/setup_redirects.c \
		$(SETUPDIR)/setup_pipes.c \
		$(SETUPDIR)/env_helper_functions.c \
		$(MAINDIR)/execute_children.c \
		$(BUILTINDIR)/ft_echo.c \
		$(BUILTINDIR)/ft_pwd.c \
		$(BUILTINDIR)/ft_export.c \
		$(BUILTINDIR)/ft_unset.c \
		$(SPLITDIR)/new_mini_split_helpers.c \
		$(SETUPDIR)/check_for_errors.c \
		$(SPLITDIR)/split_cleaner_helper_funcs.c \
		$(SPLITDIR)/potential_split_helpers.c \
		$(SETUPDIR)/child_data_helpers.c \
		$(MAINDIR)/main_helpers.c \

OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make fclean -C $(LIBFTDIR)
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all
debug: fclean $(OBJS) $(LIBFT)
		$(CC) $(DEBUGFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS)

.PHONY: all clean fclean re valgrind debug