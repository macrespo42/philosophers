NAME = philo_one

CC = clang

CFLAGS = -Wall -Wextra -Werror -I includes/

HEADER = philo_one.h

BUILTINS = main

SRC = $(addsuffix .c, $(addprefix srcs/, $(BUILTINS)))

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re