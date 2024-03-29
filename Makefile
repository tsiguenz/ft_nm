NAME = ft_nm
TEST_NAME = $(NAME)_test

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC_PATH = src/
OBJ_PATH = obj/
TEST_PATH = test/
LIBFT = libft/libft.a
LIBS = -Llibft -lft
HEADERS = -Iinclude -Ilibft

SRC_NAME = main.c \
					 nm_wrapper.c \
					 init.c \
					 x64/handle_elf.c \
					 x64/parsing.c \
					 x64/print.c \
					 x64/sort.c \
					 x64/set_type.c \
\
					 x86_32/handle_elf.c \
					 x86_32/parsing.c \
					 x86_32/print.c \
					 x86_32/sort.c \
					 x86_32/set_type.c \



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
	@touch test/bin/no_perm
	@chmod 000 test/bin/no_perm
	./$(TEST_NAME) # 2> /dev/null
	@rm -rf test/bin/no_perm

clean:
	@make clean -C libft/ --no-print-directory
	rm -rf obj

fclean: clean
	@make fclean -C libft/ --no-print-directory
	rm -rf $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
