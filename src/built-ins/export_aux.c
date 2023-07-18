#include "../../inc/minishell.h"

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int is_alpha_num(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}