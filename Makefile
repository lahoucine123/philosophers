# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/10 11:42:23 by laoubaid          #+#    #+#              #
#    Updated: 2024/05/11 13:50:04 by laoubaid         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = $(wildcard *.c)

OBJ = $(SRC:.c=.o)

NAME = philo

CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -pthread -o $(NAME) $(OBJ)

leak: $(OBJ)
	gcc $(CFLAGS) -pthread -fsanitize=address -g3 -o $(NAME) $(OBJ)

%.o: %.c
	gcc $(CFLAGS) -g3 -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all