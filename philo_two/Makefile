NAME = philo_two

SRCS = main.c\
       thread_utils.c\
       error_handler.c\
       utils.c\
       initialize_simulation.c\
       start_simulation.c\
       utils2.c\
       semaphore_utils.c

HDR = ./

RM = rm -f

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJS	= $(SRCS:%.c=%.o)

.c.o:
			$(CC) $(CFLAGS) -I$(HDR) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -I$(HDR) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re specular
