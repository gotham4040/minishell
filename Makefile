# Variables
CC = gcc
CFLAGS = -Werror -Wall -Wextra -g3
LDFLAGS = -lreadline #-fsanitize=address -static-libasan
RM = rm -rf
NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
HEADER_DIR = includes
HEADER = $(HEADER_DIR)/minishell.h

# Sources et objets
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parsing/error.c \
       	$(SRC_DIR)/parsing/1-lexer/lexer_guillmin.c \
       	$(SRC_DIR)/parsing/1-lexer/lexer_split.c \
       	$(SRC_DIR)/parsing/1-lexer/lexer_remove_guillmin.c \
       	$(SRC_DIR)/parsing/1-lexer/lexer_var_env_guillemin.c \
       	$(SRC_DIR)/parsing/1-lexer/lexer_node.c \
       	$(SRC_DIR)/parsing/2-tokeniser/find_good_token.c \
       	$(SRC_DIR)/parsing/2-tokeniser/if_cmd.c \
       	$(SRC_DIR)/parsing/3-parser/token_verif.c \
       	$(SRC_DIR)/parsing/3-parser/check_arg.c \
       	$(SRC_DIR)/parsing/utils.c \
		$(SRC_DIR)/execution/execution.c \
       	$(SRC_DIR)/execution/builtins/ft_cd.c \
       	$(SRC_DIR)/execution/builtins/ft_echo.c \
       	$(SRC_DIR)/execution/builtins/ft_env.c \
       	$(SRC_DIR)/execution/builtins/ft_exit.c \
       	$(SRC_DIR)/execution/builtins/ft_export.c \
       	$(SRC_DIR)/execution/builtins/ft_pwd.c \
       	$(SRC_DIR)/execution/builtins/ft_unset.c \
		$(SRC_DIR)/execution/builtins/exec_builtins.c \
       	$(SRC_DIR)/execution/env/env.c \
       	$(SRC_DIR)/execution/env/get_env.c \
       	$(SRC_DIR)/execution/env/sort_env.c \
       	$(SRC_DIR)/execution/system_commands/find_cmd_path_if_exist.c \
		$(SRC_DIR)/execution/free_all.c \
		$(SRC_DIR)/execution/env/shell_level.c \
		$(SRC_DIR)/execution/env/dollar_qm.c \
		$(SRC_DIR)/execution/processes/child_process_signal.c \
		$(SRC_DIR)/execution/system_commands/check_if_path_exists.c \
		$(SRC_DIR)/execution/processes/child_processes.c \
		$(SRC_DIR)/execution/pipes/wait_pipes.c \
		$(SRC_DIR)/execution/env/env_calculus.c \
		$(SRC_DIR)/execution/pipes/create_pipes.c \
		$(SRC_DIR)/execution/move_inside_list.c \
		$(SRC_DIR)/execution/pipes/return_error.c \
		$(SRC_DIR)/execution/redirections/token_stdin.c \
		$(SRC_DIR)/execution/redirections/token_stdout.c \
		$(SRC_DIR)/execution/redirections/token_heredoc.c \
		$(SRC_DIR)/execution/redirections/token_append.c \
		$(SRC_DIR)/execution/redirections/handle_tokens.c \
		$(SRC_DIR)/execution/pipes/count_pipes.c \
		$(SRC_DIR)/execution/pipes/setup_pipes.c \
		$(SRC_DIR)/execution/execution/exec_no_pipe.c \
		$(SRC_DIR)/execution/execution/exec_with_pipes.c \
		$(SRC_DIR)/execution/check_path.c \
		$(SRC_DIR)/execution/execution/error_during_fork.c \

OBJS = $(SRCS:.c=.o)

# Règles
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -o $@ $^ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[0;31mcleaned!\033[0m"

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	@echo "\033[0;31mfcleaned!\033[0m"

re: fclean all

.PHONY: all clean fclean re
