SRCS		= src/utils.c src/ft_split_marks.c src/minishell.c \
			  src/access_cmd.c src/errors.c \
			  gnl/get_next_line.c gnl/get_next_line_utils.c \
			  src/cmd/echo.c src/cmd/cd.c src/cmd/export.c \
			  src/cmd/unset.c src/cmd/exit.c src/cmd/env.c src/cmd/pwd.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

GNL			= -Ignl

RM			= rm -f

NAME		= minishell

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(GNL) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean

.PHONY: all clean fclean re
