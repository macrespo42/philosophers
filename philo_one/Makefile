NAME = philo_one

CC = clang

CFLAGS = -Wall -Wextra -Werror -lpthread

HEADER = philo_one.h

MAIN = main

SRC = $(addsuffix .c, $(MAIN))

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