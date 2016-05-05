
#LIBFT_DIR = libft
#LIBPROTOCOL_DIR = libprotocol
NAME =	astar
#LFTFLAGS = -L $(LIBFT_DIR) -lft
#LPROTOCOLFLAGS = -L $(LIBPROTOCOL_DIR) -lprotocol
OBJSERV =$(SRCSERV:src/%.cpp=.obj/%.o)
SRCSERV = 	src/main.cpp

CC		=	clang++
FLAGS	=	#-Wall -Werror -Wextra -O3
INC		=	-Iinc #-Ilibprotocol/includes -Ilibft/includes

# OS NAME
OS := $(shell uname -s)

ifeq ($(OS),Darwin)
CC_CMD = $(CC) -o $@ $(OBJSERV) #$(LPROTOCOLFLAGS) $(LFTFLAGS)
OBJ_CMD = $(CC) $(FLAGS) -o $@ -c $< $(INC)
endif
ifeq ($(OS),Linux)
CC_CMD = $(CC) -o $@ $(OBJSERV) -lSDL#$(LPROTOCOLFLAGS) $(LFTFLAGS) -Wl,--no-as-needed
OBJ_CMD = $(CC) $(FLAGS) -o $@ -c $< $(INC)
endif


.PHONY: all re clean fclean

all: $(NAME)

$(NAME): $(OBJSERV) #$(LIBFT_DIR)/libft.a $(LIBPROTOCOL_DIR)/libprotocol.a
	$(CC_CMD)

.obj/%.o: src/%.cpp
	@mkdir -p .obj/
	$(OBJ_CMD)

#$(LIBFT_DIR)/libft.a:
#	@(cd $(LIBFT_DIR) && $(MAKE))

#$(LIBPROTOCOL_DIR)/libprotocol.a:
#	@(cd $(LIBPROTOCOL_DIR) && $(MAKE))

re: fclean all

clean:
#	make -C $(LIBFT_DIR) clean
#	make -C $(LIBPROTOCOL_DIR) clean
	rm -rf $(OBJ)

fclean:
#	make -C $(LIBFT_DIR) fclean
#	make -C $(LIBPROTOCOL_DIR) fclean
	rm -rf $(OBJ)
	rm -rf $(NAME)
