NAME				=	minitalk

CL					=	client
HEADER_PATH			=	includes
CL_SRC_LST			=	srcs/utils.c srcs/client.c

SV					=	server
SV_SRC_LST			=	srcs/utils.c srcs/server.c

HEADER_PATH_BONUS	=	minitalk_bonus/includes
CL_SRC_LST_BONUS	=	minitalk_bonus/srcs/utils_bonus.c minitalk_bonus/srcs/client_bonus.c
SV_SRC_LST_BONUS	=	minitalk_bonus/srcs/utils_bonus.c minitalk_bonus/srcs/server_bonus.c

CC					=	gcc
FLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

all: $(NAME)

$(NAME): $(CL) $(SV)

$(CL): $(CL_SRC_LST)
	$(CC) $(FLAGS) -I $(HEADER_PATH) $(CL_SRC_LST) -o $(CL)

$(SV): $(SV_SRC_LST)
	$(CC) $(FLAGS) -I $(HEADER_PATH) $(SV_SRC_LST) -o $(SV)

bonus: cl_bonus sv_bonus

cl_bonus: $(CL_SRC_LST_BONUS)
	$(CC) $(FLAGS) -I $(HEADER_PATH_BONUS) $(CL_SRC_LST_BONUS) -o $(CL)

sv_bonus: $(SV_SRC_LST_BONUS)
	$(CC) $(FLAGS) -I $(HEADER_PATH_BONUS) $(SV_SRC_LST_BONUS) -o $(SV)

cl: $(CL)

sv: $(SV)

clean:

fclean: clean
	@$(RM) $(SV) $(CL) $(SV_BONUS) $(CL_BONUS) 

re: fclean all

 .PHONY: all clean sv cl fclean re sv_bonus cl_bonus $(NAME)