# By: rvesterl <rvesterl@student.42bangkok.com>

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

NAME = minishell

SRC = minishell.c \
	  debug.c \
	  init.c \
	  env_list.c \
	  env_util.c \
	  free.c \
	  signal.c \
	  error.c \
	  cmd_input.c \
	  cmd_builtin_echo.c \
	  cmd_builtin_cd.c \
	  cmd_builtin_pwd.c \
	  cmd_builtin_export.c \
	  cmd_builtin_export_no_arg.c \
	  cmd_builtin_unset.c \
	  cmd_builtin_env.c \
	  cmd_builtin_exit.c \
	  exec_builtin.c \
	  mock_exec.c \
	  mock_util.c \
	  cmd_path.c \
	  cmd_util.c \
	  cmd_list.c \
	  lexer.c \
	  lexer_char_handler.c \
	  lexer_op_handler.c \
	  lexer_quote_handler.c \
	  lexer_space_handler.c \
	  lexer_utils.c \
	  parser.c \
	  parser_cmd_table.c \
	  parser_cmd_table_utils.c \
	  parser_quotes.c \
	  parser_quote_utils.c \
	  parser_redirection.c \
	  parser_redirection_utils.c \
	  parser_utils.c \
	  parser_free.c \
	  expander_path.c \
	  expander_variable.c \
	  exec_external.c \
	  exec_external_memory.c \
	  exec_external_error.c \
	  pipe.c \
	  redirection.c \
	  redirection_input.c \
	  redirection_output.c \
	  redirection_util.c \
	  child.c \
	  buf_overflow_protection.c \
	  syntax_analysis.c \
	  redirection_heredoc.c \
	  redirection_heredoc_expand.c \
	  redirection_heredoc_util.c \
	  redirection_heredoc_error.c

HDR = .

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_BUILD = all bonus

OBJ = $(SRC:.c=.o)

.PHONY: default all clean fclean re debug

all: $(NAME)

debug: CFLAGS = -g -O0 -Wall -Wextra -Werror -D DEBUG=1
debug: LIBFT_BUILD = debug
debug: minishell

$(NAME): $(OBJ) $(LIBFT) minishell.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile minishell.h 
	$(CC) $(CFLAGS) -I $(HDR) -I $(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) $(LIBFT_BUILD)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -f $(NAME)
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
