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

static int count_expand(t_shell *shell, char *token, int *len, int *cpy)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while(token[*len])
	{	
		if (shell->var_quoted == 1 && (token[*len] == '\'' || token[*len] == '\"'))
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

static int check_quotes(char *str, int *len)
{
	int cpy_len;
	char	quote;

	cpy_len = *len;
	while(str[cpy_len] && str[cpy_len] != ' ')
	{	
		if ((str[cpy_len] == '\'' || str[cpy_len] == '\"'))
		{
			quote = str[cpy_len];
			while (str[cpy_len] != quote)
			{
				cpy_len++;

			}
		}
		else if (str[cpy_len] == ' ')
		{	
			(*len)++;
			return (1);
		}
		else
			cpy_len++;
	}
	return (0);
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

		size = count_expand(shell, str, &len, &cpy) + 1;
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		ft_arglstadd_back(&(cmd->redir_list->path_arg), ft_arglstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
	}
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
		size = count_expand(shell, str, &len, &cpy) + 1;
		printf("size is %d\n", size);
		shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		if (shell->var_cat)
			ft_arglstlast(cmd->argx)->arg = ft_strjoin(ft_arglstlast(cmd->argx)->arg, shell->tmp_tok);
		else
			ft_arglstadd_back(&(cmd->argx), ft_arglstnew(ft_strdup(shell->tmp_tok)));
		free(shell->tmp_tok);
	}
}

void expander(t_shell *shell, t_cmd **cmd)
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
			printf("arg es %s\n",cmd[n]->arg->arg);
			while (cmd[n]->arg->arg[i])
			{
				expstr = ft_strdup(expand_str(shell, cmd[n]->arg, &i, &j));
				printf("expstr es %s\n", expstr);
				free(shell->tmp_tok);
				if (expstr)
					expandstr_loop(shell, expstr, cmd[n]);
			}
			cmd[n]->arg = cmd[n]->arg->next;
			i = 0;
			j = 0;
		}
		n++;
	}
	n = 0;
	while (cmd[n])
	{	
		if (cmd[n]->redir_list)
		{
			expstr = ft_strdup(expand_str(shell, cmd[n]->redir_list->path_arg, &i, &j));
			free(shell->tmp_tok);
			if (expstr)
			{	
				free(cmd[n]->redir_list->path_arg);
				cmd[n]->redir_list->path_arg = NULL;
				expandredir_loop(shell, expstr, cmd[n]);
			}
			else
			{	
				free(cmd[n]->redir_list->path_arg);
				cmd[n]->redir_list->path_arg = NULL;
			}
		}
		n++;
	}
}