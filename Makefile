M_SRCS		= src/utils.c src/ft_split_marks.c src/minishell.c \
			  src/access_cmd.c src/errors.c src/utils_env.c \
			  src/count.c src/signal.c src/history.c src/parse.c src/redir.c
#			  src/cmd/echo.c src/cmd/cd.c src/cmd/export.c \
			  src/cmd/unset.c src/cmd/exit.c src/cmd/env.c src/cmd/pwd.c \
			
GNL_SRCS	= gnl/get_next_line.c gnl/get_next_line_utils.c

M_OBJS		= $(patsubst src/%.c, $(OBJECTS_DIR)/%.o, $(M_SRCS))

GNL_OBJS	= $(patsubst gnl/%.c, $(OBJECTS_DIR)/%.o, $(GNL_SRCS))

OBJECTS_DIR = obj

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -I inc/

LFLAGS		= -lreadline

GNL			= -Ignl

RM			= rm -f

NAME		= minishell

all:		$(NAME)

$(NAME): $(M_OBJS) $(GNL_OBJS) inc/minishell.h
	$(CC) $(CFLAGS) $(GNL) $(M_OBJS) $(GNL_OBJS) -o $(NAME) $(LFLAGS)

$(OBJECTS_DIR)/%.o : src/%.c inc/minishell.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@

$(OBJECTS_DIR)/%.o : gnl/%.c  gnl/get_next_line.h | $(OBJECTS_DIR)
	$(CC) -c  $< -o $@

$(OBJECTS_DIR) :
	mkdir -p $(OBJECTS_DIR)

clean:
	$(RM) -r $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
