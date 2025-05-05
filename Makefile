# ------------------------------ Sources ------------------------------

SRC = $(wildcard src/*.c)

OBJ = $(SRC:src/%.c=build/%.o)

# ------------------------------ Constant Strings ------------------------------

NAME = mlm_simulator

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = -I include

# ------------------------------ Colors ------------------------------

BOLD_PURPLE	=	\033[1;35m

BOLD_CYAN	=	\033[1;36m

BOLD_YELLOW	=	\033[1;33m

NO_COLOR	=	\033[0m

# ------------------------------ Messages ------------------------------

COMP_START	=	echo "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"

PROG_READY	=	echo "\n📥 MLM Assistant is ready!\n"

CLEANED		=	echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed the executables \n"

# ------------------------------ Rules ------------------------------

all:	$(NAME)

$(NAME):	$(OBJ)
	@$(COMP_START)
	@$(CC) $(OBJ) -o $(NAME)
	@$(PROG_READY)

build/%.o:	src/%.c
	@mkdir -p ./build
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	@rm -f build/*.o
	@$(CLEANED)

fclean:
	@rm -f build/*.o $(NAME)
	@$(FCLEANED)

re: fclean all

.PHONY: all run clean fclean re
