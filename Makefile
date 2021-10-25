NAME		=	minitalk

SERVER		:=	server
CLIENT		:=	client

CC :=  gcc
CFLAGS	:= -Wall -Wextra -Werror
RM	= rm -f

SRC_DIR		:= srcs
SRC_B_DIR	:= minitalk_bonus/srcs

B_DIR := minitalk_bonus

SRC_SERVER	:= ${SRC_DIR}/server.c ${SRC_DIR}/utils.c
OBJ_SERVER 	:= ${SRC_SERVER:.c=.o}

SRC_CLIENT	:= ${SRC_DIR}/client.c ${SRC_DIR}/utils.c
OBJ_CLIENT 	:= ${SRC_CLIENT:.c=.o}

SRC_SERVER_B	:= ${SRC_B_DIR}/server_bonus.c ${SRC_B_DIR}/utils_bonus.c
OBJ_SERVER_B 	:= ${SRC_SERVER_B:.c=.o}

SRC_CLIENT_B	:= ${SRC_B_DIR}/client_bonus.c ${SRC_B_DIR}/utils_bonus.c
OBJ_CLIENT_B 	:= ${SRC_CLIENT_B:.c=.o}

all:	${NAME}

${NAME}: ${SERVER} ${CLIENT} 

${SERVER}: ${OBJ_SERVER} minitalk.h
	@ ${CC} ${CFLAGS} -o ${SERVER} ${OBJ_SERVER}
	@echo "server is ready"	

${CLIENT}: ${OBJ_CLIENT} minitalk.h
	@ ${CC} ${CFLAGS} -o ${CLIENT} ${OBJ_CLIENT}
	@echo "client is ready"	

bonus:  server_bonus client_bonus
		
server_bonus: ${OBJ_SERVER_B} ${B_DIR}/minitalk_bonus.h
	@ ${CC} ${CFLAGS} -I ${B_DIR} -o ${SERVER} ${OBJ_SERVER_B}
	@echo "server bonus is ready"	

client_bonus: ${OBJ_CLIENT_B} ${B_DIR}/minitalk_bonus.h
	@ ${CC} ${CFLAGS} -I ${B_DIR} -o ${CLIENT} ${OBJ_CLIENT_B}
	@echo "client bonus is ready"	

clean:
		rm -rf ${OBJ_CLIENT} ${OBJ_SERVER} ${OBJ_CLIENT_B} ${OBJ_SERVER_B}

fclean: clean
		${RM} ${SERVER} ${CLIENT}

re:		fclean all

.PHONY: all clean fclean re bonus server_bonus client_bonus
	







