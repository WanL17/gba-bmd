CC      = gcc

CFLAGS 	= -Iinclude

NAME    = sdk

SRC    	= src/sdk.c \
		  src/input/input.c \
		  src/lib/array.c \
		  src/lib/error.c \
		  src/lib/display.c

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
