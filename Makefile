CC      = gcc

CFLAGS 	= -Iinclude -g3

NAME    = sdk

SRC    	= src/sdk.c \
		  src/input/input.c \
		  src/input/error.c \
		  src/header/dump/dump.c \
		  src/header/dump/infos.c \
		  src/header/dump/display.c \
		  src/header/generator/gen.c \
		  src/header/generator/file.c \
		  src/lib/array.c \
		  src/lib/error.c \
		  src/lib/display.c \
		  src/lib/hexa.c \
		  src/lib/bits.c \
		  src/lib/string.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY : all clean fclean re
