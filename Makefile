NAME = minishell
SRC = main.c sig_handler.c
UTILS = utils1.c
LIB = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC) $(UTILS)
	@make -s -C libft
	@gcc $(SRC) $(UTILS) $(CFLAGS) $(LIB) -o $(NAME) -lreadline

clean:
	@make clean -s -C libft

fclean:
	@make fclean -s -C libft
	@rm -f $(NAME)

re: fclean all