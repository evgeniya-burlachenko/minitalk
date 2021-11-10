# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:18:15 by skelly            #+#    #+#              #
#    Updated: 2021/11/10 14:44:29 by skelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minitalk

SV				=	server
CL				=	client

CC 				=  gcc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f

SRC_DIR			= srcs
SRC_B_DIR		= minitalk_bonus/srcs

B_DIR 			= minitalk_bonus

SRC_SERVER		= $(SRC_DIR)/server.c $(SRC_DIR)/utils.c
SRC_CLIENT		= $(SRC_DIR)/client.c $(SRC_DIR)/utils.c

SRC_SERVER_B	= $(SRC_B_DIR)/server_bonus.c $(SRC_B_DIR)/utils_bonus.c
SRC_CLIENT_B	= $(SRC_B_DIR)/client_bonus.c $(SRC_B_DIR)/utils_bonus.c

all:	$(NAME)

$(NAME): $(SV) $(CL)

$(SV): minitalk.h
	@ $(CC) $(CFLAGS) -o $(SV) $(SRC_SERVER)
	@echo "server is ready"	

$(CL): minitalk.h
	@ $(CC) $(CFLAGS) -o $(CL) $(SRC_CLIENT)
	@echo "client is ready"	

bonus:  server_bonus client_bonus
		
server_bonus:$(SRC_SERVER_B) $(B_DIR)/minitalk_bonus.h
	@ $(CC) $(CFLAGS)  $(SRC_SERVER_B)  -o $(SV)
	@echo "server bonus is ready"	

client_bonus:$(SRC_CLIENT_B) $(B_DIR)/minitalk_bonus.h
	@ $(CC) $(CFLAGS) $(SRC_CLIENT_B) -o $(CL)
	@echo "client bonus is ready"	

clean:
		
fclean: clean
		@$(RM) $(SV) $(CL)

re:		fclean all

.PHONY: all clean fclean re bonus server_bonus client_bonus
	
