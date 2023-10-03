/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:35:45 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/03 13:58:40 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_double_list
{
	int						content;
	struct s_double_list	*next;
	struct s_double_list	*prev;
}		t_dlist;

/* 
libc
*/
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
void		*ft_memset(void *b, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int64_t		ft_atoi(char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(char *s1);
/*
additional
*/
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f) (unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
size_t		ft_putstr(char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl(char *s);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_putnbr(int n);
void		ft_putnbr_fd(int n, int fd);
/*lists - bonus*/
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*new ones*/
size_t		ft_putadd(void *ptr);
size_t		ft_putunbr(unsigned int n);
size_t		ft_puthexnbr(unsigned int n, char *base);
int			ft_contains_digit(char *str);
t_dlist		*ft_dlstnew(int content);
void		ft_dlstadd_back(t_dlist **head, t_dlist **tail, t_dlist *new);
t_dlist		*ft_dlstlast(t_dlist *lst);
void		ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void		ft_reverse_tab(int *tab, int n);
void		ft_printarr(int *arr, int n);
char		*ft_strcat(char *dest, char *src);

/*printf*/
size_t		check_conversions(va_list args, char const *str);
int			ft_printf(char const *str, ...);
size_t		ft_printadd(void *ptr);
size_t		ft_printchar(char c);
size_t		ft_printhex(unsigned int n, char *base);
size_t		ft_printnbr(int n);
size_t		ft_printstr(char *s);
size_t		ft_printunbr(unsigned int n);
int			ft_isprint(int c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/*get_next_line*/
char		*get_next_line(int fd);
char		*ft_get_strjoin(char *tmp, char *buf, size_t n);
size_t		ft_get_strchr(const char *s, int c, int n);
void		ft_get_strlcpy(char *dst, const char *src,
				size_t dstsize, unsigned int start);
size_t		ft_get_strlen(const char *s);
char		*ft_get_free(char *tmp);

#endif
