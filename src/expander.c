#include  "../inc/minishell.h"

static int count_expand(char *token, int *len, int *cpy)
{
	int i;

	i = 0;
	while(token[i] || token [i])
	{

	}
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
		size = count_expand(str, &len, &cpy) + 1;
	/* 	shell->tmp_tok = (char *)malloc(sizeof (char) * size);
		copy_token(shell->tmp_tok, str, &cpy, size);
		ft_lstadd_back(&(shell->expanded), ft_lstnew(ft_strdup(shell->tmp_tok)));
		free (shell->tmp_tok); */
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
		expstr = expand_str(shell, shell->tokens);
		//expand_loop(shell, expstr);
		shell->tokens = shell->tokens->next;
	}	
}