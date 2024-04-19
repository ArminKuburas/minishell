# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvalimak <tvalimak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 11:16:12 by akuburas          #+#    #+#              #
#    Updated: 2024/04/16 19:11:28 by tvalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RLFLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
#RLFLAGS = -lreadline -L

MAKE = make bonus
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS = main.c \
		mini_split.c \
		mini_split_counter.c \
		input_list_functions.c \
		create_env_list.c \
		type_assigner.c \
		signal.c \
		echo.c \
		cd.c \
		pwd.c \
		export.c

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

.PHONY: all clean fclean re valgrind