#include "../inc/minishell.h"

int count_len_quotes(char *str)
{	
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\"')
			i++;
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}

char	*get_redir(char *line)
{
	while (*line == '>' || *line == '<')
		line++;
	while (*line == ' ')
		line++;
	return (line);
}

int	count_redir_arr(char **args)
{
	int	i;
	int	c;
	
	i = 0;
	c = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>')
			c++;
		i++;
	}
	return (c);
}

