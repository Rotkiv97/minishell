NAME = minishell

SRC = main.c ft_gest_ambiental.c
SRC_TEST = main_test.c split_quotes.c

UTILS = utils1.c utils1_free.c

LIB = ./libft/libft.a
GNL = ./gnl/get_next_line_utils_bonus.c ./gnl/get_next_line_bonus.c

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC) $(UTILS)
	@make -s -C libft
	@gcc $(SRC) $(UTILS) $(CFLAGS) $(LIB) -o $(NAME) -lreadline

test: $(SRC_TEST) $(UTILS)
	@make -s -C libft
	@gcc $(SRC_TEST) $(UTILS) $(GNL) $(CFLAGS) $(LIB) -o $(TEST) -lreadline

clean:
	@make clean -s -C libft

fclean:
	@make fclean -s -C libft
	@rm -f $(NAME)
	@rm -f $(TEST)

re: fclean all