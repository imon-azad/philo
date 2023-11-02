# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 16:14:11 by esamad-j          #+#    #+#              #
#    Updated: 2023/11/02 16:18:10 by esamad-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = check_init.c exit.c main.c thread.c utils.c

OBJS		= $(SRCS:%.c=%.o)

CFLAGS		= -Wall -Werror -Wextra  

CC 			= gcc 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re