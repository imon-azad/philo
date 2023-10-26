# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 16:14:11 by esamad-j          #+#    #+#              #
#    Updated: 2023/10/26 20:15:07 by esamad-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = check_init.c exit.c ft_minilibft.c main.c thread.c

OBJS		= $(SRCS:%.c=%.o)

#-g -fsanitize=thread 
CFLAGS		=  -Wall -Werror -Wextra  #-g -fsanitize=thread 

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