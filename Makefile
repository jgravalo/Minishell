M_SRCS		= src/utils.c src/ft_split_marks.c src/minishell.c src/pipes.c src/prompt2.c \
			  src/access_cmd.c src/errors.c src/utils_env.c src/here_doc.c src/prompt.c \
			  src/count.c src/signal.c src/history.c src/parse.c src/redir.c src/close_fd.c \
			  src/lexer.c src/lexer_aux.c src/utils2.c src/utils3.c src/utils4.c src/meta.c \
			  src/parse_others.c src/parse_quotes.c src/meta.c

BUILT_SRCS	= src/built-ins/echo.c src/built-ins/cd.c src/built-ins/export.c \
			  src/built-ins/unset.c src/built-ins/env.c src/built-ins/pwd.c src/built-ins/run_builtin.c \
			  src/built-ins/export_aux.c src/built-ins/export_n.c
			
#GNL_SRCS	= gnl/get_next_line.c gnl/get_next_line_utils.c

M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))

BUILT_OBJS	= $(patsubst src/built-ins/%.c, $(OBJECTS_DIR)/%.o, $(BUILT_SRCS))

#GNL_OBJS	= $(patsubst gnl/%.c, $(OBJECTS_DIR)/%.o, $(GNL_SRCS))

OBJECTS_DIR = obj

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I inc/

LFLAGS		= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LRFLAG		= -lreadline

#GNL			= -Ignl

RM			= rm -f

NAME		= minishell

all:		$(NAME)

$(NAME): $(M_OBJS) $(BUILT_OBJS) $(GNL_OBJS) inc/minishell.h
	$(CC) $(CFLAGS) $(M_OBJS) $(BUILT_OBJS) -o $(NAME) $(LFLAGS) $(LRFLAG)

$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@ -I ~/.brew/opt/readline/include

#$(OBJECTS_DIR)/%.o : gnl/%.c  gnl/get_next_line.h | $(OBJECTS_DIR)
#	$(CC) -c  $< -o $@

$(OBJECTS_DIR)/%.o : src/built-ins/%.c  src/built-ins/builtins.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@

$(OBJECTS_DIR) :
	mkdir -p $(OBJECTS_DIR)

clean:
	$(RM) -r $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
