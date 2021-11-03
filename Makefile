NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
GNULIB_DIR = /usr/local/opt/readline/lib
GNUINC_DIR = /usr/local/opt/readline/include
LIBFT_DIR = Libft
INC_DIR = incs
SRC_DIR = srcs
OBJS =  ${SRCS:.c=.o}
SRCS =  $(SRC_DIR)/main.c \
		$(SRC_DIR)/parse/parse.c \
		$(SRC_DIR)/parse/pipe_redir.c \
		$(SRC_DIR)/parse/empty_q.c \
		$(SRC_DIR)/parse/heredoc.c \
		$(SRC_DIR)/parse/env.c \
		$(SRC_DIR)/parse/utils.c \
		$(SRC_DIR)/parse/copy.c \
		$(SRC_DIR)/parse/str.c \
		$(SRC_DIR)/parse/strs.c \
		$(SRC_DIR)/parse/cont_pipe.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/qsort.c \
		$(SRC_DIR)/utils/ft_strtoimax.c \
		$(SRC_DIR)/run.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/puterror.c \
		$(SRC_DIR)/chkerror.c \
		$(SRC_DIR)/redirection.c \
		$(SRC_DIR)/heredoc.c \
		$(SRC_DIR)/environ.c \
		$(SRC_DIR)/pipe.c \
		$(SRC_DIR)/stream.c \
		$(SRC_DIR)/path.c \
		$(SRC_DIR)/cmd.c \
		$(SRC_DIR)/term.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/variable.c \
		$(SRC_DIR)/builtin/islegal.c \
		$(SRC_DIR)/builtin/builtin.c \
		$(SRC_DIR)/builtin/builtin_common.c \
		$(SRC_DIR)/builtin/cd.c \
		$(SRC_DIR)/builtin/pwd.c \
		$(SRC_DIR)/builtin/env.c \
		$(SRC_DIR)/builtin/echo.c \
		$(SRC_DIR)/builtin/exit.c \
		$(SRC_DIR)/builtin/unset.c \
		$(SRC_DIR)/builtin/export.c \
		$(SRC_DIR)/builtin/option.c

all : $(NAME)

$(NAME) : $(OBJS) lft
	$(CC) $(CFLAGS) -ltermcap -lncurses \
	-L $(GNULIB_DIR) -lreadline -lhistory \
	-L $(LIBFT_DIR) -lft \
	$(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ \
	-I $(GNUINC_DIR) \
	-I $(INC_DIR)

# libft compile
lft :
	@$(MAKE) -C $(LIBFT_DIR) all

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re : fclean all
