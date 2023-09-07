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
	char quote;

	j = count_len_quotes(str);
	new_str = (char *)malloc(sizeof (char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i])
	{	
		if (str[i] == '\"' || str[i] == '\'')
		{	
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				new_str[j] = str[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
	}
	new_str[j] = '\0';
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

