NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror

GREEN   = \033[1;32m
CYAN    = \033[1;36m
YELLOW  = \033[1;33m
ORANGE  = \033[38;5;208m
RED     = \033[1;31m
RESET   = \033[0m
CLEAR   = \033[2J\033[H

SRCS    = src/main.c \
		  src/lexer/lexer.c \
		  src/lexer/lexer_utils.c \
		  src/lexer/lexer_utils2.c \
		  src/parser/parser.c \
		  src/parser/parser_utils.c \
		  src/parser/parser_utils_2.c\
          src/expander/expander.c \
		  src/expander/expander_utils.c \
		  src/expander/expander_utils_bis.c \
          src/executor/executor.c \
		  src/executor/exec_utils.c \
          src/executor/exec_path.c \
          src/executor/exec_redir.c \
		  src/executor/exec_pipe.c \
		  src/executor/bridge.c \
		  src/executor/bridge_utils.c \
          src/builtins/builtins.c \
          src/builtins/builtins_bis.c \
          src/builtins/builtins_utils.c \
		  src/builtins/builtins_utils_bis.c \
		  src/signal/signal.c\

OBJS    = $(SRCS:.c=.o)
TOTAL   = $(words $(SRCS))

LIBFT       = libft/libft.a
LIBFT_DIR   = libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@printf "\n"
	@printf "$(GREEN)✔ $(NAME) compilé avec succès !$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I includes -I libft -c $< -o $@
	@count=$$(ls -1 $(OBJS) 2>/dev/null | wc -l); \
	percent=$$((count * 100 / $(TOTAL))); \
	filled=$$((percent / 2)); \
	bar=$$(printf '#%.0s' $$(seq 1 $$filled)); \
	printf "\r$(CYAN)[%-50s] %d%%$(RESET)" "$$bar" "$$percent"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@if [ -t 1 ]; then \
		printf "$(CLEAR)$(YELLOW)\n          *\n$(RESET)"; sleep 0.15; \
		printf "$(CLEAR)$(YELLOW)\n        .'.'.\n         '*'\n$(RESET)"; sleep 0.15; \
		printf "$(CLEAR)$(ORANGE)\n      .  *  .\n     * *** *\n      .  *  .\n$(RESET)"; sleep 0.2; \
		printf "$(CLEAR)$(ORANGE)\n    *  .  *  .  *\n   .  * ***** *  .\n    *  .  *  .  *\n$(RESET)"; sleep 0.2; \
		printf "$(CLEAR)$(RED)\n  *  *  .  ***  .  *  *\n *  .  ********* .  *\n  *  *  .  ***  .  *  *\n$(RESET)"; sleep 0.25; \
		printf "$(CLEAR)$(RED)\n\n          BOOM MINISHELL\n$(RESET)"; sleep 0.4; \
		printf "$(CLEAR)$(GREEN)✔ minishell entièrement supprimé.$(RESET)\n"; \
	else \
		echo "minishell entièrement supprimé."; \
	fi

re: fclean all

.PHONY: all clean fclean re