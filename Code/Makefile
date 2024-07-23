# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fallan <fallan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 13:37:49 by francis           #+#    #+#              #
#    Updated: 2024/07/23 18:26:37 by fallan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./lib/libft.a

FT_PRINTF = ./lib/libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFLAGS = -L./lib -lft -lftprintf -lreadline

SRCS = main.c tokenization.c tokenization-checkers.c

SRC = $(addprefix srcs/, $(SRCS))

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(FT_PRINTF): $(LIBFT)
	make -C ./lib/ft_printf -f Makefile

$(LIBFT):
	make -C ./lib/libft -f Makefile

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o minishell

sanitize: CFLAGS += -fsanitize=address
sanitize: re

debug: CFLAGS += -g
debug: re

clean:
	rm -f $(OBJ)
	for dir in ./lib/libft ./lib/ft_printf; do \
		$(MAKE) -C $$dir clean; \
	done

fclean: clean
	rm -f $(OBJ) $(NAME)  
# $(FT_PRINTF) $(LIBFT)
	for dir in ./lib/libft ./lib/ft_printf; do \
		$(MAKE) -C $$dir fclean; \
	done

re: fclean all

.PHONY: all sanitize debug clean fclean re