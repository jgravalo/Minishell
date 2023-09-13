#include "../inc/minishell.h"

static int count_pipes(t_tok *tokens)
{	
	int count;

	count = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->type, "PIPE") == 0)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static int redir_type(t_tok *token)
{
	if (ft_strcmp(token->token, "<") == 0)
		return (IN);
	if (ft_strcmp(token->token, ">") == 0)
		return (OUT);
	if (ft_strcmp(token->token, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(token->token, "<<") == 0)
		return (HERE);
}

static void init(t_cmd **cmd, int n)
{	
	int i;

	i = 0;
	while (i < n)
	{	
		cmd[i] = malloc(sizeof (t_cmd));
		cmd[i]->redir_list = NULL;
		cmd[i]->arg = NULL;
		i++;
	}
	cmd[i] = NULL;
}

static void alloc_args(t_cmd **cmd, t_tok *tokens)
{	
	int i;
	int n;

	n = 0;
	i = 0;
	while(tokens)
	{
		if (ft_strcmp(tokens->type, "WORD") == 0)
			n++;
		else if (ft_strcmp(tokens->type, "PIPE") == 0)
			cmd[i++]->args = malloc(sizeof (char *) * (n + 1));
		tokens = tokens->next;
	}
	cmd[i]->args = malloc(sizeof (char *) * (n + 1));
}

static void parse(t_tok *tokens, t_cmd **cmd)
{
	
	int j;
	int redir;

	j = 0;
	redir = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->type, "WORD") == 0)
			ft_arglstadd_back(&(cmd[j]->arg), ft_arglstnew(ft_strdup(tokens->token)));
		else if (ft_strcmp(tokens->type, "REDIR") == 0)
		{	
			redir = redir_type(tokens);
			tokens = tokens->next;
			ft_redirlstadd_back(&(cmd[j]->redir_list), ft_redirlstnew(redir));
			ft_arglstadd_back(&(ft_redirlstlast(cmd[j]->redir_list)->path_arg), ft_arglstnew(tokens->token));
		}
		else // pipe, nuevo command struct
			j++;
		tokens = tokens->next;
	}
	j++;
	cmd[j] = NULL;
}


void parser(t_shell *shell)
{	
	int n;

	n = count_pipes(shell->tokens);
	shell->s_cmd = malloc(sizeof (t_cmd *) * (n + 2));
	init(shell->s_cmd, n + 1);
	parse(shell->tokens, shell->s_cmd);
}