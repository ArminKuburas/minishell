# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 11:16:12 by akuburas          #+#    #+#              #
#    Updated: 2024/05/24 16:28:35 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
SRCDIR = source_files
BUILTINDIR = $(SRCDIR)/builtins
MAINDIR = $(SRCDIR)/main_signal_and_execution
SETUPDIR = $(SRCDIR)/setup_and_data_handling
SPLITDIR = $(SRCDIR)/split_and_cleaner
OBJDIR = object_files

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
		$(MAINDIR)/signal_helpers.c \
		$(BUILTINDIR)/ft_cd.c \
		$(BUILTINDIR)/ft_env.c \
		$(SETUPDIR)/set_up_child_data.c \
		$(SETUPDIR)/setup_commands.c \
		$(SETUPDIR)/setup_helpers.c \
		$(SETUPDIR)/setup_is_it_command.c \
		$(SETUPDIR)/setup_redirects.c \
		$(SETUPDIR)/setup_pipes.c \
		$(SETUPDIR)/env_helper_functions.c \
		$(MAINDIR)/execute_children.c \
		$(BUILTINDIR)/ft_echo.c \
		$(BUILTINDIR)/ft_exit.c \
		$(BUILTINDIR)/error_msgs.c \
		$(BUILTINDIR)/ft_exit_format_check.c \
		$(BUILTINDIR)/ft_pwd.c \
		$(BUILTINDIR)/ft_export.c \
		$(BUILTINDIR)/export_helpers.c \
		$(BUILTINDIR)/export_unset_helpers.c \
		$(BUILTINDIR)/ft_unset.c \
		$(SPLITDIR)/new_mini_split_helpers.c \
		$(SETUPDIR)/check_for_errors.c \
		$(SPLITDIR)/split_cleaner_helper_funcs.c \
		$(SPLITDIR)/potential_split_helpers.c \
		$(SETUPDIR)/child_data_helpers.c \
		$(MAINDIR)/main_helpers.c \
		$(MAINDIR)/child_handling.c \
		$(MAINDIR)/child_cleaning_functions.c \
		$(MAINDIR)/child_execute_help_functions.c \
		$(SETUPDIR)/setup_command_helpers.c \
		$(SETUPDIR)/setup_redirect_helpers.c \
		$(SETUPDIR)/setup_heredoc.c \
		$(SETUPDIR)/heredoc_modify_input.c \
		$(MAINDIR)/additional_helpers.c \
		$(MAINDIR)/syntax_printers.c \
		$(MAINDIR)/assign_command_type.c \

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make fclean -C $(LIBFTDIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re  debug