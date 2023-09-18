UTILS_DIR	= src/utils

M_SRCS		= src/alloc_envp.c src/builtin.c src/categorizer.c src/errors.c src/errors2.c src/free_sh.c \
			  src/execute.c  src/execute_heredoc.c src/execute_heredoc_aux.c  src/execute_redir.c src/execute_pipes.c  \
			  src/expander.c src/expander_arg.c src/expander_redir.c src/expander_string.c  src/expander_count.c \
			  src/expander_aux.c   src/lexer.c src/lexer_count.c  src/lexer_len.c src/lexer_count_aux.c \
			  src/main.c  src/minishell.c  src/parent.c src/parser.c src/pipes.c  src/quote_remove.c  \
			  src/search.c  src/set_argv.c 	  
 
BUILT_SRCS	= src/built-ins/echo.c src/built-ins/cd.c src/built-ins/cd_aux.c src/built-ins/export.c \
			  src/built-ins/unset.c src/built-ins/env.c src/built-ins/pwd.c  \
			  src/built-ins/export_aux.c src/built-ins/export_n.c src/built-ins/exit.c \
			  src/built-ins/compare_exit.c src/built-ins/ft_builtins.c

UTILS_SRCS	= $(UTILS_DIR)/utils_list_arg.c $(UTILS_DIR)/utils_list_quote.c $(UTILS_DIR)/utils_list_redir.c \
			  $(UTILS_DIR)/utils_list_tok.c $(UTILS_DIR)/utils_other.c $(UTILS_DIR)/utils_print.c \
			  $(UTILS_DIR)/utils_print2.c $(UTILS_DIR)/utils_str.c $(UTILS_DIR)/utils_str2.c $(UTILS_DIR)/ft_itoa.c \
			  $(UTILS_DIR)/utils_str3.c $(UTILS_DIR)/utils_env.c $(UTILS_DIR)/utils_free.c 
			
M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))

BUILT_OBJS	= $(patsubst src/built-ins/%.c, $(OBJECTS_DIR)/%.o, $(BUILT_SRCS))

UTILS_OBJS	= $(patsubst src/utils/%.c, $(OBJECTS_DIR)/%.o, $(UTILS_SRCS))

OBJECTS_DIR = obj

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I inc/

LFLAGS		= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LRFLAG		= -lreadline

RM			= rm -f

NAME		= minishell

all:		$(NAME)

$(NAME): $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) $(GNL_OBJS) inc/minishell.h
	$(CC) -g $(CFLAGS) $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) -o $(NAME) $(LFLAGS) $(LRFLAG)

$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h  | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@ -I ~/.brew/opt/readline/include $(CFLAGS)

$(OBJECTS_DIR)/%.o : src/built-ins/%.c  inc/builtins.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@

$(OBJECTS_DIR)/%.o : src/utils/%.c inc/utils.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@

$(OBJECTS_DIR) :
	mkdir -p $(OBJECTS_DIR)

clean:
	$(RM) -r $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
