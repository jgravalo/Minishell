#include "../../inc/minishell.h"

static int count_quotes(char *var)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while(var[i])
	{
		if (var[i] == '\"')
			c++;
		else if (var[i] == '\\')
			c++;
		i++;
	}
	return (c);
}

char *protect_quotes(char *var)
{
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	if (count_quotes(var) == 0)
		return (var);
	new = malloc(sizeof (char) * (ft_strlen(var) + count_quotes(var) + 1));
	while(var[i])
	{
		if (var[i] == '\"')
		{
			new[j++] = '\\';
			new[j++] = var[i++];
		}
		else if (var[i] == '\\')
		{
			new[j++] = '\\';
			new[j++] = var[i++];
		}
		else
			new[j++] = var[i++];
	}
	return (new);
}