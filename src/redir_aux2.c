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

char *remove_quotes(char *str)
{
	int i;
	int j;
	char *new_str;

	j = count_len_quotes(str);
	new_str = (char *)malloc(sizeof (char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{	
		if (str[i] == '\"' || str[i] == '\"')
			i++;
		else
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
	return (new_str);
}

char	*get_redir(char *line)
{
	while (*line == '>' || *line == '<')
		line++;
	while (*line == ' ')
		line++;
	return (line);
}