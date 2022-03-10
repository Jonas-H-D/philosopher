# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 14:48:04 by jhermon-          #+#    #+#              #
#    Updated: 2022/03/10 16:19:28 by jhermon-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = threading.c itoa.c utils.c atoi.c

CC = gcc

NAME = philo

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

THREADS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
			@echo "\n\033[0;33mCompiling..."
	    $(CC) $(FLAGS) $(THREADS) -o $(NAME) $(OBJ)
			@echo "\033[0m"

$(OBJ): $(SRC)
		$(CC) $(FLAGS) -c $(SRC)

clean:
		@echo "\033[0;31mCleaning..."
		rm -f $(OBJ)
		@echo "\033[0m"

fclean: clean
		@echo "\033[0;31mRemoving executable..."
		rm -f $(NAME)
		@echo "\033[0m"

re: fclean all

.PHONY: all clean fclean re%