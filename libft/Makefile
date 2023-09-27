NAME = libft.a

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c \
		ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
		ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c \
		ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putunbr.c ft_puthexnbr.c ft_contains_digit.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c ft_dlstnew.c ft_dlstadd_back.c ft_dlstlast.c ft_dlstadd_front.c ft_reverse_tab.c \
		ft_printarr.c
		
OBJS =  $(SRCS:.c=.o)

PRINT_DIR = printf

GET_DIR = get_next_line

PRINT_SRCS = $(addprefix $(PRINT_DIR)/,ft_isprint.c ft_printadd.c ft_printchar.c ft_printf.c ft_printhex.c ft_printnbr.c ft_printstr.c ft_printunbr.c)

PRINT_OBJS = $(PRINT_SRCS:.c=.o)

GET_SRCS = $(addprefix $(GET_DIR)/,get_next_line_utils.c get_next_line.c)

GET_OBJS = $(GET_SRCS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I .

all: $(NAME)

$(NAME) : $(OBJS) $(PRINT_OBJS) $(GET_OBJS)
	ar rcs $(NAME) $(OBJS) $(PRINT_OBJS)  $(GET_OBJS)

%.o : %.c ./libft.h
	gcc -c  $(CFLAGS) $< -o $@

clean:
	rm -f *.o 
	cd printf && rm -f *.o
	cd get_next_line && rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all bonus clean fclean re
