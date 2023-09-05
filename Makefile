NAME = ft_nm
TEST_NAME = $(NAME)_test

CC = gcc
FLAGS = -g3 -Wall -Wextra -Werror

SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/
LIBFT = libft/libft.a
LIBS = -Llibft -lft
HEADERS = -Iinclude -Ilibft

SRC_NAME = main.c \
					 nm_wrapper.c
TEST_SRC_NAME = test_main.c
OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
TEST_SRC = $(addprefix $(TEST_PATH), $(TEST_SRC_NAME))

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(HEADERS) -MMD -c $< -o $@

-include $(OBJ:%.o=%.d)

all: $(NAME)

$(LIBFT):
	@make -C libft/ --no-print-directory

test:
	$(CC) $(FLAGS) $(HEADERS) $(LIBS) -D __IS_TEST__ $(TEST_SRC) $(SRC) -o $(TEST_NAME)

clean:
	@make clean -C libft/ --no-print-directory
	rm -rf obj

fclean: clean
	@make fclean -C libft/ --no-print-directory
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
