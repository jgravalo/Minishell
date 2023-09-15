#include  "../inc/minishell.h"

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
			copy_exp(shell->tmp_tok, str, &cpy, size);
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

void expand_args(t_shell *shell, t_cmd **cmd)
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