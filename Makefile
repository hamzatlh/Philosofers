# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 00:40:00 by htalhaou          #+#    #+#              #
#    Updated: 2023/06/12 22:39:49 by htalhaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  philo.c \
		utils.c \
		ft_atoi.c \
		check_arg.c \
		utils_2.c

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

RM = rm -f

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
