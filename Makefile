# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsoteldo <gsoteldo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 20:53:47 by gsoteldo          #+#    #+#              #
#    Updated: 2024/03/04 18:14:54 by gsoteldo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

NAME_CLIENT = client
NAME_SERVER = server
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_CLIENT = client.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER = server.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) libft
	@echo "Compilando cliente"
	@make -C libft
	$(CC) $(OBJ_CLIENT) -L libft -lft -o $(NAME_CLIENT)
	@echo "$(GREEN)-----------------Cliente Compilado-----------------$(NC)"

$(NAME_SERVER): $(OBJ_SERVER) libft
	@make -C libft
	$(CC) $(OBJ_SERVER) -L libft -lft -o $(NAME_SERVER)
	@echo "$(GREEN)------------------Server Compilado------------------$(NC)"

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	@make clean -C libft

fclean: clean
	rm -f client server
	@make fclean -C libft
	@echo "$(RED)-----------------Borrado cliente y/o servidor-----------------$(NC)"

re: fclean all

.PHONY: all client server clean fclean re