# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 13:14:28 by achane-l          #+#    #+#              #
#    Updated: 2022/02/02 16:10:51 by achane-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo
SRCS =	philo.c\
		init_philos.c\
		free_utils.c\
		utils.c

OBJS := ${SRCS:.c=.o}

all: ${NAME}
	@printf "That's compile\n"
$(NAME): ${OBJS}
	@gcc -Wall -Werror -Wextra -o $(NAME) $(OBJS) -pthread -g3
%.o: %.c
	$(CC) -Wall -Werror -Wextra -c $< -o $@
clean:
	@printf "Soft Cleaning\n"
	@rm -rf *.o

fclean: clean
	@printf "Hard clean"
	@rm -rf $(NAME)

re:	fclean all

PHONY: all bonus clean fclean re