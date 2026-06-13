NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

SRCS    = src/main.c \
		  src/lexer/lexer.c \
		  src/lexer/lexer_utils.c \
		  src/lexer/lexer_utils2.c \
		  src/parser/parser.c \
		  src/parser/parser_utils.c \
          src/expander/expander.c \
          src/executor/executor.c \
		  src/executor/exec_utils.c \
          src/executor/exec_path.c \
          src/executor/exec_redir.c \
		  src/executor/exec_pipe.c \
		  src/executor/bridge.c \
          src/builtins/builtins.c \
          src/builtins/builtins_bis.c \
          src/builtins/builtins_utils.c \
		  src/builtins/builtins_utils_bis.c

OBJS    = $(SRCS:.c=.o)

LIBFT       = libft/libft.a
LIBFT_DIR   = libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -I libft -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
