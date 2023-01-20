# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 17:55:43 by tsiguenz          #+#    #+#              #
#    Updated: 2023/01/20 21:07:58 by tsiguenz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
TEST_NAME = $(NAME)_test

CC = gcc
FLAGS = -g3 -Wall -Wextra -Werror

SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/
INC = -Iinclude -Isrc

SRC_NAME = main.c max.c
TEST_SRC_NAME = test_main.c
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
TEST_SRC = $(addprefix $(TEST_PATH), $(TEST_SRC_NAME))

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INC) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

all: $(NAME)

# Test rule
test:
	$(CC) $(FLAGS) $(INC) -D __IS_TEST__ $(TEST_SRC) $(SRC) -o $(TEST_NAME)

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
