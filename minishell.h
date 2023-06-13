# ifndef MINISHELL_H
# define MINISHELL_H

# include "gnl/get_next_line.h"

int		parse_line(char *line);

size_t	ft_strlen(const char *str);

int		ft_strcmp(char *s1, char *s2);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

#endif
