MAKEFLAGS += --no-print-directory
NAME		= minishell

LIBFT_DIR	= libft

LIBFT 		= $(LIBFT_DIR)/libft.a

UTILS_DIR	= src/utils

BUILT_DIRS	= src/built-ins

CC			= gcc

OBJECTS_DIR = obj

M_SRCS		= $(addprefix src/, alloc_envp.c builtin.c categorizer.c errors.c errors2.c free_sh.c \
			  execute.c  execute_heredoc.c execute_heredoc_aux.c  execute_redir.c execute_pipes.c  \
			  expander.c expander_arg.c expander_redir.c expander_string.c  expander_count.c \
			  expander_aux.c   lexer.c lexer_count.c  lexer_len.c lexer_count_aux.c \
			  main.c  minishell.c  parent.c parser.c parser_aux.c pipes.c  quote_remove.c  \
			  search.c  set_argv.c  syntax_errors.c reviser.c)
 
BUILT_SRCS	= $(addprefix $(BUILT_DIRS)/, echo.c cd.c cd_aux.c export.c unset.c env.c pwd.c export_aux.c export_n.c exit.c \
			  compare_exit.c ft_builtins.c export_aux2.c)

UTILS_SRCS	= $(addprefix $(UTILS_DIR)/, utils_list_arg.c utils_list_quote.c utils_list_redir.c utils_list_tok.c utils_other.c \
			  utils_print.c utils_print2.c utils_env.c utils_free.c)
			
M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))

BUILT_OBJS	= $(patsubst src/built-ins/%.c, $(OBJECTS_DIR)/%.o, $(BUILT_SRCS))

UTILS_OBJS	= $(patsubst src/utils/%.c, $(OBJECTS_DIR)/%.o, $(UTILS_SRCS))

LFLAGS		= -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

LRFLAG		= -lreadline

CFLAGS		= -Wall -Werror -Wextra -I inc/

RM			= rm -f

all: make_libft	$(NAME)

$(NAME): $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) $(GNL_OBJS) $(LIBFT) inc/minishell.h
	$(CC) -g $(CFLAGS) $(M_OBJS) $(BUILT_OBJS) $(UTILS_OBJS) -o $(NAME) $(LFLAGS) $(LRFLAG) -L$(LIBFT_DIR) -lft

$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h  Makefile | $(OBJECTS_DIR)
	$(CC) -c $(CFLAGS)  $< -o $@ -I ~/.brew/opt/readline/include

$(OBJECTS_DIR)/%.o : src/built-ins/%.c  inc/builtins.h Makefile| $(OBJECTS_DIR)
	$(CC) -c $(CFLAGS)  $< -o $@

$(OBJECTS_DIR)/%.o : src/utils/%.c inc/utils.h Makefile | $(OBJECTS_DIR)
	$(CC) -c $(CFLAGS)  $< -o $@

$(OBJECTS_DIR) :
	mkdir -p $(OBJECTS_DIR)

make_libft:
	@make -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJECTS_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
