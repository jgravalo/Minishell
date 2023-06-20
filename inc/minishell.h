# ifndef MINISHELL_H
# define MINISHELL_H

#include <fcntl.h>
//# include <defines.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
# include <unistd.h>
# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define DEF_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:"
# include "../gnl/get_next_line.h"

int		cmd_error(char *str);

size_t	ft_strlen(const char *str);

int		ft_strcmp(char *s1, char *s2);

char	*ft_strchr(char *str, int c);

char	*ft_strjoin(char *s1, char *s2);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	**ft_split(char const *s, char c);

void	free_m(char **fdf);

int		search_var(char *name, char **envp);

char	*file_cmd(char *cmd, char **envp);

#endif
