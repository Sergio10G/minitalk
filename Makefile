# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdiez-ga <sdiez-ga@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 19:01:51 by sdiez-ga          #+#    #+#              #
#    Updated: 2022/07/21 20:42:23 by sdiez-ga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk

SERVER		=	server

CLIENT		=	client

SERVER_SRC	=	src/server.c

CLIENT_SRC	=	src/client.c

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

%o			:	%c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(SERVER) $(CLIENT)

$(SERVER)	:	$(SERVER_OBJ) src/utils.o
				$(CC) -o $(SERVER) $(SERVER_OBJ) src/utils.o

$(CLIENT)	:	$(CLIENT_OBJ) src/utils.o
				$(CC) -o $(CLIENT) $(CLIENT_OBJ) src/utils.o

all			:	$(NAME)

clean		:	
				$(RM) $(SERVER_OBJ)
				$(RM) $(CLIENT_OBJ)
				$(RM) src/utils.o

fclean		:	clean
				$(RM) $(SERVER)
				$(RM) $(CLIENT)

re			:	fclean all

.PHONY		:	all clean fclean re
