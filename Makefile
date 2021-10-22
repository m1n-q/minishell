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
		$(SRC_DIR)/ft_split_space.c \
		$(SRC_DIR)/ft_split_space_env.c \
		$(SRC_DIR)/ft_split_space_utils.c \
		$(SRC_DIR)/ft_split_space_cpy.c \
		$(SRC_DIR)/ft_split_space_str.c \
		$(SRC_DIR)/ft_split_space_strs.c \
		$(SRC_DIR)/parse.c \
		$(SRC_DIR)/run.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/builtin.c \
		$(SRC_DIR)/redirection.c \
		$(SRC_DIR)/environ.c \
		$(SRC_DIR)/pipe.c \
		$(SRC_DIR)/stream.c \
		$(SRC_DIR)/path.c \
		$(SRC_DIR)/cmd.c


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
