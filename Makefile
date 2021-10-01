NAME =	philo

SRC =	philo2.c\
		philo3.c\
		philo4.c\
		ft_atoi.c
		


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
