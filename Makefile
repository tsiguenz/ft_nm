# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsiguenz <tsiguenz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/09 17:55:43 by tsiguenz          #+#    #+#              #
#    Updated: 2023/01/21 17:31:11 by tsiguenz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm
TEST_NAME = $(NAME)_test

CC = gcc
FLAGS = -g3 -Wall -Wextra -Werror

SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/
LIBFT = -Llibft -lft
INC = -Iinclude -Isrc -Ilibft

SRC_NAME = main.c
TEST_SRC_NAME = test_main.c
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
TEST_SRC = $(addprefix $(TEST_PATH), $(TEST_SRC_NAME))

$(NAME): $(OBJ)
	@make -C libft/ --no-print-directory
	$(CC) $(FLAGS) $(INC) $(LIBFT) $(OBJ) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

all: $(NAME)

# Test rule
test:
	$(CC) $(FLAGS) $(INC) $(LIBFT) -D __IS_TEST__ $(TEST_SRC) $(SRC) -o $(TEST_NAME)

clean:
	@make clean -C libft/ --no-print-directory
	rm -rf obj

fclean: clean
	@make fclean -C libft/ --no-print-directory
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
