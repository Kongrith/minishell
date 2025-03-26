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
	  error.c

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
