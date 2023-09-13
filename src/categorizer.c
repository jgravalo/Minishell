#include  "../inc/minishell.h"

void categorizer(t_tok *tokens)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->token, "|") == 0)
			tokens->type = "PIPE";
		else if (ft_strcmp(tokens->token, ">") == 0
			|| ft_strcmp(tokens->token, "<") == 0
			|| ft_strcmp(tokens->token, ">>") == 0
			|| ft_strcmp(tokens->token, "<<") == 0)
			tokens->type = "REDIR";
		else
			tokens->type = "WORD";
		tokens = tokens->next;
	}
}