#include  "../inc/minishell.h"

static void (count_quote(char *token, int *len, int *cpy, int *count))
{	
	char	quote;

	quote = token[*len];
	(*count)++;
	(*len)++;
	while (token[*len] != quote)
	{
		(*count)++;
		(*len)++;
	}
	(*count)++;
	(*len)++;
}

static int count_expand(char *token, int *len, int *cpy)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while(token[*len])
	{	
		if (token[*len] == '\'' || token[*len] == '\"')
			count_quote(token, len, cpy, &count);
		else if (token[*len] == ' ')
		{	
			(*len)++;
			return (count);
		}
		else
		{
			count++;
			(*len)++;
		}
	}
	return (count);
}

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int		i;
	int 	quote;

	i = 0;
	while (i < (dstsize - 1))
	{	
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	(*cpy)++;
	dst[i] = '\0';
}

static void expand_loop(t_shell *shell, char *str)
{
	int	i;
	int	len;
	int	cpy;
	int	size;

	i = 0;
	len = 0;
	cpy = 0;
	size = 0;
	while (str[len])
	{	
		while (str[len] == ' ')
		{
			len++;
			cpy++;
		}
		size = count_expand(str, &len, &cpy) + 1;
		printf("siz ees %d\n", size);
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		ft_lstadd_back(&(shell->expanded), ft_lstnew(ft_strdup(shell->tmp_tok)));
		free (shell->tmp_tok);
	}
}

void expander(t_shell *shell)
{	
	int i;
	char *expstr;
	shell->expanded = NULL;

	i = 0;
	while (shell->tokens)
	{	
		expstr = ft_strdup(expand_str(shell, shell->tokens));
		free(shell->tmp_tok);
		if (expstr)
			expand_loop(shell, expstr);
		shell->tokens = shell->tokens->next;
	}	
}