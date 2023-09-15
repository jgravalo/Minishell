#include "../inc/minishell.h"

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
			copy_exp(shell->tmp_tok, str, &cpy, size);
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


void expand_redir(t_shell *shell, t_cmd **cmd)
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