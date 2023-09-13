#include  "../inc/minishell.h"

void categorizer(t_tok *expanded)
{
	while (expanded)
	{
		if (ft_strcmp(expanded->token, "|") == 0)
			expanded->type = "PIPE";
		else if (ft_strcmp(expanded->token, ">") == 0
			|| ft_strcmp(expanded->token, "<") == 0
			|| ft_strcmp(expanded->token, ">>") == 0
			|| ft_strcmp(expanded->token, "<<") == 0)
			expanded->type = "REDIR";
		else
			expanded->type = "WORD";
		expanded = expanded->next;
	}
}