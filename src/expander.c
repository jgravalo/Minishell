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

static void expandstr_loop(t_shell *shell, char *str, t_cmd *cmd)
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
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		printf("tmp es %s\n", shell->tmp_tok);
		ft_arglstadd_back(&(cmd->arg), ft_arglstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
	}
}

static void expandredir_loop(t_shell *shell, char *str, t_cmd *cmd)
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
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		printf("tmp es %s\n", shell->tmp_tok);
		ft_arglstadd_back(&(cmd->redir_list->path_arg), ft_arglstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
	}
}

void expander(t_shell *shell, t_cmd **cmd)
{	
	int i;
	char *expstr;

	i = 0;
	while (cmd[i])
	{	
		expstr = ft_strdup(expand_str(shell, cmd[i]->arg));
		printf("expanded es %s\n", expstr);
		free(shell->tmp_tok);
		if (expstr)
		{	
			free(cmd[i]->arg);
			cmd[i]->arg = NULL;
			expandstr_loop(shell, expstr, cmd[i]);
		}
		i++;
	}
	i = 0;
	while (cmd[i])
	{	
		expstr = ft_strdup(expand_str(shell, cmd[i]->redir_list->path_arg));
		printf("expanded es %s\n", expstr);
		free(shell->tmp_tok);
		if (expstr)
		{	
			free(cmd[i]->redir_list->path_arg);
			cmd[i]->redir_list->path_arg = NULL;
			expandredir_loop(shell, expstr, cmd[i]);
		}
		else
		{	
			free(cmd[i]->redir_list->path_arg);
			cmd[i]->redir_list->path_arg = NULL;
		}
		i++;
	}
}