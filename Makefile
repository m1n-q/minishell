NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
GNULIB_DIR = /usr/local/opt/readline/lib
GNUINC_DIR = /usr/local/opt/readline/include
LIBFT_DIR = Libft
LIBFT = Libft/libft.a
INC_DIR = incs
SRC_DIR = srcs
OBJS =  ${SRCS:.c=.o}
SRCS =  $(SRC_DIR)/main.c \
		$(SRC_DIR)/run.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/getter.c \
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
		$(SRC_DIR)/loop.c \
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
		$(SRC_DIR)/parse/error.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/utils/qsort.c \
		$(SRC_DIR)/utils/ft_strtoimax.c \
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

# colors
BG_BLACK   = \033[40m
BG_RED     = \033[41m
BG_GREEN   = \033[42m
BG_YELLOW  = \033[43m
BG_BLUE    = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN    = \033[46m
BG_LGREY   = \033[47m
BG_DGREY   = \033[100m
BG_LRED    = \033[101m
BG_LGREEN  = \033[102m
BG_LYELLOW = \033[103m
BG_LBLUE   = \033[104m
BG_LMAGENTA= \033[105m
BG_LCYAN   = \033[106m
BG_WHITE   = \033[107m

FG_BLACK   = \033[30m
FG_RED     = \033[31m
FG_GREEN   = \033[32m
FG_YELLOW  = \033[33m
FG_BLUE    = \033[34m
FG_MAGENTA = \033[35m
FG_CYAN    = \033[36m
FG_LGREY   = \033[37m
FG_DGREY   = \033[90m
FG_LRED    = \033[91m
FG_LGREEN  = \033[92m
FG_LYELLOW = \033[93m
FG_LBLUE   = \033[94m
FG_LMAGENTA= \033[95m
FG_LCYAN   = \033[96m
FG_WHITE   = \033[97m

CL_BOLD   = \033[1m
CL_DIM    = \033[2m
CL_UDLINE = \033[4m
CL_BLINK  = \033[5m
CL_INVERT = \033[7m
CL_HIDDEN = \033[8m

NO_COLOR = \033[0m

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS) link
	$(CC) $(CFLAGS) -ltermcap -lncurses \
	-L $(GNULIB_DIR) -lreadline -lhistory \
	-L $(LIBFT_DIR) -lft \
	$(OBJS) -o $@



$(SRC_DIR)/parse/%.o: $(SRC_DIR)/parse/%.c compile1
	$(CC) $(CFLAGS) -c $< -o $@ -I $(GNUINC_DIR) -I $(INC_DIR)

$(SRC_DIR)/utils/%.o: $(SRC_DIR)/utils/%.c compile2
	$(CC) $(CFLAGS) -c $< -o $@ -I $(GNUINC_DIR) -I $(INC_DIR)

$(SRC_DIR)/builtin/%.o: $(SRC_DIR)/builtin/%.c compile3
	$(CC) $(CFLAGS) -c $< -o $@ -I $(GNUINC_DIR) -I $(INC_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c compile0
	$(CC) $(CFLAGS) -c $< -o $@ -I $(GNUINC_DIR) -I $(INC_DIR)

# libft compile
$(LIBFT) :
	@echo "${FG_DGREY}"
	@echo "Compiling Libft . . ."
	@echo "${NO_COLOR}"
	@$(MAKE) -C $(LIBFT_DIR) all

clean : cleanup
	@$(MAKE) -C $(LIBFT_DIR) clean --silent
	@rm -rf $(OBJS)

fclean : clean fcleanup
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent
	@rm -rf $(NAME)

re : fclean all

compile0 :
	@echo "${FG_LRED}"
	@echo "Compiling default sources . . ."
	@echo "${NO_COLOR}"

compile1 :
	@echo "${FG_LGREEN}"
	@echo "Compiling parse . . ."
	@echo "${NO_COLOR}"

compile2 :
	@echo "${FG_LYELLOW}"
	@echo "Compiling utils . . ."
	@echo "${NO_COLOR}"

compile3 :
	@echo "${FG_CYAN}"
	@echo "Compiling builtin . . ."
	@echo "${NO_COLOR}"

link :
	@echo "${FG_MAGENTA}"
	@echo "${CL_BOLD}Linking object files . . ."
	@echo "${NO_COLOR}"

cleanup :
	@echo "\n🗑  removing all object files . . ."

fcleanup :
	@echo "\n🗑  removing all binary files . . ."

.INTERMEDIATE : compile0 compile1 compile2 compile3 link cleanup fcleanup
