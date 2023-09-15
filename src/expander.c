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

static int count_expand(t_shell *shell, char *token, int *len)
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

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int		i;
	int 	quote;

	i = 0;
	//printf("str before cpy es %s\n", &src[*cpy]);
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

static void redir_loop(t_shell *shell, char *str, t_cmd *cmd)
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
		//printf("str es %s, len is %d\n", str, len);
		if (shell->quote && shell->quote->start == len)
			shell->var_quoted = 1;
		else
			shell->var_quoted = 0;
		size = count_expand(shell, str, &len) + 1; 
		if (size > 1)
		{
			shell->tmp_tok = (char *)malloc(sizeof (char) * size);
			copy_token(shell->tmp_tok, str, &cpy, size);
			if (shell->var_quoted)
			{
				shell->tmp_tok = remove_quotes(shell, shell->tmp_tok);
				shell->quote = shell->quote->next;
			}
			if (shell->var_cat)
				ft_arglstlast(cmd->redir_x->path_arg)->arg = ft_strjoin(ft_arglstlast(cmd->redir_x->path_arg)->arg, ft_strdup(shell->tmp_tok));
			else
			{	
				if (!shell->next_redir)
				{
					ft_redirlstadd_back(&(cmd->redir_x), ft_redirlstnew(cmd->redir_list->type)); // ycopiamos nodo en nueva lista
					shell->next_redir = 1; // tenemos que seguir copiando nuevos args, si tocase, hasta que en funcion anterior cambiamos de redir struct
				}
				ft_arglstadd_back(&(ft_redirlstlast(cmd->redir_x)->path_arg), ft_arglstnew(ft_strdup(shell->tmp_tok)));
			}
			free(shell->tmp_tok);
		}
	}
}

static void arg_loop(t_shell *shell, char *str, t_cmd *cmd)
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
		//printf("str es %s, index is %d\n", str, len);
		if (shell->quote && len == shell->quote->start)
			shell->var_quoted = 1;
		else
			shell->var_quoted = 0;
		size = count_expand(shell, str, &len) + 1;
		//printf("size %d, cat %d, quote %d\n", size, shell->var_cat, shell->var_quoted);
		if (size > 1)
		{
			shell->tmp_tok = (char *)malloc(sizeof (char) * size);
			copy_token(shell->tmp_tok, str, &cpy, size);
			//printf("tmp es %s\n", shell->tmp_tok);
			if (shell->var_quoted)
			{
				shell->tmp_tok = remove_quotes(shell, shell->tmp_tok);
				shell->quote = shell->quote->next;
			}
			//printf("tmp after remove quotes es %s\n", shell->tmp_tok);
			if (shell->var_cat)
				ft_arglstlast(cmd->argx)->arg = ft_strjoin(ft_arglstlast(cmd->argx)->arg, ft_strdup(shell->tmp_tok));
			else
				ft_arglstadd_back(&(cmd->argx), ft_arglstnew(ft_strdup(shell->tmp_tok)));	
			free(shell->tmp_tok);
		}
	}
	shell->quote = NULL;
}

static  void expand_args(t_shell *shell, t_cmd **cmd)
{
	int i;
	int j;
	int n;
	char *expstr;

	i = 0;
	j = 0;
	n = 0;
	while (cmd[n])
	{	
		cmd[n]->argx = NULL;
		while (cmd[n]->arg)
		{	
			while (cmd[n]->arg->arg[i])
			{
				expstr = ft_strdup(expand_str(shell, cmd[n]->arg, &i, &j));
			//	printf("expstr es %s\n", expstr);
				free(shell->tmp_tok);
				if (expstr)
					arg_loop(shell, expstr, cmd[n]);
			}
			cmd[n]->arg = cmd[n]->arg->next;
			i = 0;
			j = 0;
		}
		n++;
	}	
}

static void expand_redir(t_shell *shell, t_cmd **cmd)
{
	int i;
	int j;
	int n;
	char *expstr;

	shell->next_redir = 0;
	i = 0;
	j = 0;
	n = 0;
	while (cmd[n])
	{	
		while (cmd[n]->redir_list)
		{	
			while (cmd[n]->redir_list->path_arg->arg[i])
			{
				expstr = ft_strdup(expand_str(shell, cmd[n]->redir_list->path_arg, &i, &j));
				free(shell->tmp_tok);
				if (expstr)
					redir_loop(shell, expstr, cmd[n]);
			}
			cmd[n]->redir_list = cmd[n]->redir_list->next;
			shell->next_redir = 0;
			i = 0;
			j = 0;
		}
		n++;
	}
}

void expander(t_shell *shell, t_cmd **cmd)
{	
	shell->quote = NULL;
	expand_args(shell, cmd);
	expand_redir(shell, cmd);
}