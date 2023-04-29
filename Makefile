NAME = minishell
SRC = main.c

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	@make -s -C libft
	@gcc $(SRC) $(CFLAGS) -o $(NAME) -lreadline

clean:
	@make clean -s -C libft

fclean:
	@make fclean -s -C libft
	@rm -f $(NAME)

re: fclean all