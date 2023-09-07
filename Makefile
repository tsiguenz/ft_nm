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
					 nm_wrapper.c \
					 init.c \

TEST_SRC_NAME = test_main.c \
								set_fd_tests.c \
								set_file_size_tests.c \
								check_format_tests.c \
								set_arch_tests.c \

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

test: $(LIBFT)
	@$(CC) $(FLAGS) $(HEADERS) -D __IS_TEST__ $(TEST_SRC) $(SRC) $(LIBS) -o $(TEST_NAME)
	./$(TEST_NAME) # 2> /dev/null

clean:
	@make clean -C libft/ --no-print-directory
	rm -rf obj

fclean: clean
	@make fclean -C libft/ --no-print-directory
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
