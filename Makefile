# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 13:18:32 by welow             #+#    #+#              #
#    Updated: 2024/01/31 11:42:23 by welow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client

NAME2 = server

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CLIENT_SRC = client.c

SERVER_SRC = server.c

BONUS_CLIENT_SRC = client_bonus.c

BONUS_SERVER_SRC = server_bonus.c

OBJ_CLIENT_SRC = $(CLIENT_SRC:.c=.o)

OBJ_SERVER_SRC = $(SERVER_SRC:.c=.o)

OBJ_BONUS_CLIENT_SRC = $(BONUS_CLIENT_SRC:.c=.o)

OBJ_BONUS_SERVER_SRC = $(BONUS_SERVER_SRC:.c=.o)

all: $(NAME) $(NAME2)

$(NAME) : $(OBJ_CLIENT_SRC)
	make -C libft
	cp libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ_CLIENT_SRC) libft.a -o $@

$(NAME2) : $(OBJ_SERVER_SRC)
	$(CC) $(CFLAGS) $(OBJ_SERVER_SRC) libft.a -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C libft
	rm -f $(OBJ_CLIENT_SRC)
	rm -f $(OBJ_SERVER_SRC)
	rm -f $(OBJ_BONUS_SERVER_SRC)
	rm -f $(OBJ_BONUS_CLIENT_SRC)
	rm -f libft.a

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME2)
	make fclean -C libft

re : fclean all

bonus: $(OBJ_BONUS_SERVER_SRC) $(OBJ_BONUS_CLIENT_SRC)
	make -C libft
	cp libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ_BONUS_SERVER_SRC) libft.a -o $(NAME2)
	$(CC) $(CFLAGS) $(OBJ_BONUS_CLIENT_SRC) libft.a -o $(NAME)

.PHONY : all clean fclea re 