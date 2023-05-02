NAME = minishell
SRC = main.c sig_handler.c split_quotes.c
SRC_TEST = main_test.c split_quotes.c
UTILS = utils1.c
LIB = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC) $(UTILS)
	@make -s -C libft
	@gcc $(SRC) $(UTILS) $(CFLAGS) $(LIB) -o $(NAME) -lreadline

test: $(SRC_TEST) $(UTILS)
	@gcc $(SRC_TEST) $(UTILS) $(CFLAGS) $(LIB) -o $(NAME) -lreadline

clean:
	@make clean -s -C libft

fclean:
	@make fclean -s -C libft
	@rm -f $(NAME)

re: fclean all