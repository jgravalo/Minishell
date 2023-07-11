#include "../inc/minishell.h"

int 	is_pipe_or_dollar(char c)
{	
	if (c == '|' || c == '$')
		return (1);
	return (0);
}

int	is_redir(char *str)
{	
	int i;

	i = 0;
	if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (2);
	else if (str[i] == '<' || str[i] == '>')
		return (1);
	else
		return (0);
}

static int	count_meta(char *line, int *i, int *tokens, int word)
{	
	if (is_pipe_or_dollar(line[*i]) == 1)
	{	
		(*tokens)++;
		if (word == 1)
			(*tokens)++;
		(*i)++;
		return (1);
	}
	else if (is_redir(&line[*i]) == 2)
	{	
		(*tokens)++;
		if (word == 1)
			(*tokens)++;
		(*i) += 2;
		return (1);
	}
	else if (is_redir(&line[*i]) == 1)
	{	
		(*tokens)++;
		if (word == 1)
			(*tokens)++;
		(*i)++;
		return (1);
	}
	return (0);
}

static void loop(char *line, int *i, int *tokens, int *word)
{
	if (count_meta(line, i, tokens, *word) > 0)
		*word = 0;
	else if(line[*i] != ' ' && *word == 0)
	{	
		(*i)++;
		*word = 1;
	}
	else if (line[*i] == ' ' && *word == 1)
	{	
		(*tokens)++;
		(*i)++;
		*word = 0;
	}
	else
		(*i)++;
}

int	count_tokens(char *line)
{
	int i;
	int tokens;
	int word;

	i = 0;
	tokens = 0;
	word = 0;
	while (line[i])
		loop(line, &i, &tokens, &word);
	if (word == 1)	
		tokens++;
	return (tokens);
}
