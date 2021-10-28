# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skelly <skelly@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:18:15 by skelly            #+#    #+#              #
#    Updated: 2021/10/28 19:39:34 by skelly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minitalk

SV					=	server
SV_SRC_LST			=	srcs/utils.c srcs/server.c

CL					=	client
CL_SRC_LST			= 	srcs/utils.c srcs/client.c

HEADER_PATH_BONUS	=	minitalk_bonus
CL_SRC_LST_BONUS	=	minitalk_bonus/srcs/utils_bonus.c minitalk_bonus/srcs/client_bonus.c
SV_SRC_LST_BONUS	=	minitalk_bonus/srcs/utils_bonus.c minitalk_bonus/srcs/server_bonus.c

CC 					=	gcc
FLAGS				=	-Wall -Wextra -Werror
RM					=	rm -f

all:	${NAME}

${NAME}: ${SV} ${CL} 

${SV}: ${SV_SRC_LST} minitalk.h
	@ ${CC} ${FLAGS} -o ${SV} ${SV_SRC_LST}
	@echo "server is ready"	

${CL}: $(CL_SRC_LST) minitalk.h
	@ ${CC} ${FLAGS} -o ${CL} ${CL_SRC_LST}
	@echo "client is ready"	

bonus:  sv_bonus cl_bonus
		
sv_bonus: $(SV_SRC_LST_BONUS) ${HEADER_PATH_BONUS}/minitalk_bonus.h
	@ ${CC} ${FLAGS} -I ${HEADER_PATH_BONUS} $(SV_SRC_LST_BONUS) -o ${SV}
	@echo "server bonus is ready"	

cl_bonus: $(CL_SRC_LST_BONUS) ${HEADER_PATH_BONUS}/minitalk_bonus.h
	@ ${CC} ${FLAGS} -I ${HEADER_PATH_BONUS} $(CL_SRC_LST_BONUS) -o ${CL}
	@echo "client bonus is ready"	

clean:
		rm -rf ${OBJ_CLIENT} ${OBJ_SERVER}

fclean: clean
		${RM} ${SV} ${CL}

re:		fclean all

.PHONY: all clean fclean re bonus server_bonus client_bonus
	
