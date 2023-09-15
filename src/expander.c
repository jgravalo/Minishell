#include  "../inc/minishell.h"

static void count_quote(char *token, int *len, int *count, t_quote *quote)
{	
	while (*len != quote->end)
	{
		(*count)++;
		(*len)++;
	}
	(*count)++;
	(*len)++;
}

int count_expand(t_shell *shell, char *token, int *len)
{
	int count;
	int i;
	t_quote *ptr;

	i = 0;
	count = 0;
	ptr = shell->quote;
	shell->var_cat = 0;
	//printf("estamos en %s\n", &token[*len]);
	if (*len && token[*len] && token[*len - 1] && token[*len - 1] != ' ')
		shell->var_cat = 1;
	while(token[*len])
	{
		if (shell->var_quoted == 1 && *len == ptr->start)
		{
			count_quote(token, len, &count, ptr);
			return (count);
		}
		else if (shell->quote && shell->var_quoted == 0 && *len == shell->quote->start)
			return (count);
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

void	copy_exp(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int	i;
	int	quote;

	i = 0;
	while (src[*cpy] == ' ')
		(*cpy)++;
	while (i < (dstsize - 1))
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

void	expander(t_shell *shell, t_cmd **cmd)
{
	shell->quote = NULL;
	expand_args(shell, cmd);
	expand_redir(shell, cmd);
}