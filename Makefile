M_SRCS		= src/utils.c src/ft_split_marks.c src/minishell.c src/pipes.c src/prompt2.c \
			  src/access_cmd.c src/errors.c src/utils_env.c src/here_doc.c src/prompt.c src/child.c \
			  src/count.c src/history.c src/parse.c src/redir.c src/close_fd.c src/parse_pipes.c \
			  src/lexer.c src/lexer_aux.c src/utils2.c src/utils3.c src/utils4.c src/meta.c src/init_shell.c \
			  src/parse_no_pipes.c src/parse_quotes.c src/ft_itoa.c src/parent.c src/main.c src/init_envp.c src/redir_aux.c \
			  src/redir_aux2.c src/redir_prepare.c src/meta_utils.c src/set_redir.c src/expander.c src/utils5.c src/expander_count.c

BUILT_SRCS	= src/built-ins/echo.c src/built-ins/cd.c src/built-ins/export.c \
			  src/built-ins/unset.c src/built-ins/env.c src/built-ins/pwd.c src/built-ins/run_builtin.c \
			  src/built-ins/export_aux.c src/built-ins/export_n.c src/built-ins/exit.c src/built-ins/compare_exit.c \
			  src/built-ins/protect_quotes.c
			
M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))

BUILT_OBJS	= $(patsubst src/built-ins/%.c, $(OBJECTS_DIR)/%.o, $(BUILT_SRCS))

OBJECTS_DIR = obj

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I inc/

LFLAGS		= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LRFLAG		= -lreadline

RM			= rm -f

NAME		= minishell

all:		$(NAME)

$(NAME): $(M_OBJS) $(BUILT_OBJS) $(GNL_OBJS) inc/minishell.h
	$(CC) -g $(CFLAGS) $(M_OBJS) $(BUILT_OBJS) -o $(NAME) $(LFLAGS) $(LRFLAG)

$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@ -I ~/.brew/opt/readline/include

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
