NAME =	philo

SRC =	philo1.c\
		


OBJS = ${SRC:.c=.o}



 CC = gcc

all : $(NAME)

$(NAME) : ${OBJS}
		
		$(CC) $(SRC) -o  $(NAME) -g3

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all
