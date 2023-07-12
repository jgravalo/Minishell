#include "../inc/minishell.h"

int		len_heredoc(char *line)
{
	int i;

	i = 0;
	if (*line == '<' && *(line + 1) == '<' && ++i && ++i)
		line += 2;
	while (*line && *line == ' ' && ++i)
		line++;
	while (*line && *line != ' ' && ++i)
		line++;
	while (*line && *line == ' ' && ++i)
		line++;
	return (i);
}

int		count_heredoc(char *line)
{
	int i;

	i = 0;
	while (*line != '\0')
	{
		if (*line == '<' && *(line + 1) == '<' && ++i)
			line += len_heredoc(line);
		if (*line && !(*line == '<' && *(line + 1) == '<') && ++i)
			while (*line && !(*line == '<' && *(line + 1) == '<'))
				line++;
	}
	return (i);
}

char	**ft_split_heredoc(char *line)
{
	char	**m;
	int		i;
	int		j;
	int len;

//	printf("count = %d\n", count_redir(line));
//	printf("aqui\n");
	m = (char **)malloc(sizeof(char *) * (count_heredoc(line) + 1));
	j = -1;
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			len = len_heredoc(line);
			m[++j] = ft_substr(line, 0, len);
			line += len;
//			printf("m[%d] = |%s|\n", j, m[j]);
		}
		else
		{
			i = 0;
			while (*line && *line != '<' && *line != '>' && ++i)
				line++;
			m[++j] = ft_substr(line - i, 0, i);
//			printf("m[%d] = |%s|\n", j, m[j]);
		}
	}
	m[++j] = NULL;
	return (m);
}

char	*make_heredoc(char *line)
{
	char **tmp;

	tmp = ft_split_marks(line, ' ');
	printf("tmp[1] = %s\n", tmp[1]);
	free(tmp[0]);
	free(tmp);
	return (tmp[1]);
}

char	last_sign(char *line)
{
	int	i;

	i = 0;
	while (line[i + 1])
		i++;
	while (line[i] == ' ')
		i--;
	return (line[i]);
}

char	*find_heredoc(char *cmd, char **here_doc)
{
	char	*c;
	int		j;

	c = ft_strdup("");
	j = 0;
	while (here_doc[j])
	{
		printf("here_doc = %s\n", here_doc[j]);
		while (ft_strcmp(c, here_doc[j]) != 0)
		{
			if (last_sign(cmd) == '|')
				cmd = ft_strjoin(cmd, c);
//			free(c);
//	printf("aqui\n");
			c = readline("> ");
			printf("c = %s\n", c);
			printf("cmd = %s\n", cmd);
		}
		free(c);
		j++;
	}
	free_m(here_doc);
	return (cmd);
}

char	*parse_heredoc(char *line)
{
	char **args;
	char **here_doc;
	char *cmd;
	char *c;
	int i;
	int j;

	cmd = ft_strdup("");
	c = NULL;
	args = ft_split_heredoc(line);
	here_doc = (char **)malloc(sizeof(char *) * (count_heredoc(line) + 1));
//	printf("aqui\n");
	i = 0;
	j = -1;
	while (args[i])
	{
		if (args[i][0] == '<' && args[i][1] == '<')
		{
			here_doc[++j] = make_heredoc(args[i]);
			printf("args[%d] = |%s|\n", i, args[i]);
		}
		else
		{
//			printf("args[%d] = |%s|\n", i, args[i]);
			c = cmd;
			cmd = ft_strjoin(cmd, ft_strdup(args[i]));
			free(c);
//			printf("cmd = |%s|\n", cmd);
		}
		i++;
	}
	free_m(args);
	cmd = find_heredoc(cmd, here_doc);
	return (cmd);
}
/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	
	printf("len = %d\n", len_heredoc(argv[1]));
	printf("count = %d\n", count_heredoc(argv[1]));
	char **m = ft_split_heredoc(argv[1]);
	int i;
	for (i = 0; m[i]; i++)
		printf("m[%d] = |%s|\n", i, m[i]);
	
	char *cmd = parse_heredoc(argv[1]);
	printf("cmd = |%s|\n", cmd);
	return (0);
}*/
