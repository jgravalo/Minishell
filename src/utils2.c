#include "../inc/minishell.h"

int	is_meta(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '$')
		return (1);
	else
		return (0);
}