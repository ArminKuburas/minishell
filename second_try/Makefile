# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 11:16:12 by akuburas          #+#    #+#              #
#    Updated: 2024/05/02 11:15:35 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RLFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
DEBUGFLAGS = -Wall -Wextra -Werror -g

MAKE = make bonus
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS =	main.c \
		input_list_functions.c \
		create_env_list.c \
		type_assigner.c \
		split_cleaner.c \
		split_cleaner_dollar_functions.c \
		cleaner_length_functions.c \
		potential_split_functions.c \
		new_mini_split.c \
		signal.c \
		cd.c \
		pwd.c \
		export.c \
		unset.c \
		echo.c \
		env.c \
		heredoc.c \
		set_up_child_data.c \
		setup_commands.c \
		setup_helpers.c \
		setup_is_it_command.c \
		setup_redirects.c \
		setup_pipes.c \
		env_helper_functions.c \
		execute_children.c \
		ft_echo.c \
		ft_pwd.c \
		new_mini_split_helpers.c \
		check_for_errors.c \
		split_cleaner_helper_funcs.c \
		potential_split_helpers.c \
		child_data_helpers.c \

OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

valgrind: $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(RLFLAGS) -g

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