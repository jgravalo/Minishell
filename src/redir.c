#include "../inc/minishell.h"

//int	search_redir(char **args)
/*
char	*next_word(char *line, int *len)
{
	int		i;
	int		j++;
	char	*c;

	i = 0;
	while (*line == ' ' && j++)
		line++;
	while (*line && *line != ' ' && ++i && ++j)
		line++;
	c = ft_substr(line - i, 0, i);
	*len = j;
	return (c);
}

char	*check_redir(char *line)
{
//	int fd;
	int i;
	char *file;
	int len_redir;

	i = 0;
	len_redir;
	while (*line)
	{
		if (*line == '>' && *(line + 1) >= '>')
			file = next_word(line + 2);
		else if (*line == '>' || *line == '<')
			file = next_word(line + 1);
		printf("*line = %c\n", *line);
/
		if (*line == '>' && *(line + 1) != '>')
		{

			fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 00644); // > salida
			dup2(fd, 1);
			line += len_redir();
		}
		else if (*line == '>' && *(line + 1) == '>')
		{
			fd = open(file, O_RDWR | O_CREAT | O_APPEND, 00644); // >> salida
			dup2(fd, 1);
		}
		else if (*line == '<' && *(line + 1) != '<')
		{
			fd = open(file, O_RDONLY); // < entrada
			dup2(fd, 0);
		}
/
		else if (*line == '<' && *(line + 1) == '<')
		{
			pipe(p);
			file = ft_substr(); // modificado para here_doc
			pid = fork();
			if (pid == 0)
			{
				close(p[0]);
				dup2(p[1], 1);
				parse_pipex(file);
			}
			if ()
			waitpid(pid, NULL, 0);
		}
*		
		free(file);		
*
		line++;
	}
	return (line);
}
*/
int		len_redir(char *line)
{
	int i;
	int j;
	char *here_doc;
	char *tmp;
	int len_heredoc;

	i = 1;
	if (*line == '<' && *(line + 1) == '<')
	{
		j = 0;
		line += 2;
		i += 2;
		while (*line == ' ' && ++i)
			line++;
		while (*line != ' ' && ++i && j++)
			line++;
		here_doc = ft_substr(line - j, 0, j);
		len_heredoc = ft_strlen(here_doc);
		tmp = ft_substr(line, 0, len_heredoc);
		while (ft_strcmp(here_doc, tmp) != 0 && i++ && ++line)
			tmp = ft_substr(line, 0, len_heredoc);
		i += len_heredoc;
	}
	else
	{
		line++;
		if (*line == '>' && ++i)
			line++;
		while (*line == ' ' && ++i)
			line++;
		while (*line != ' ' && ++i)
			line++;
	}
	return (i);
}

int		count_redir(char *line)
{
	int i;

	while (*line != '\0')
	{
		printf("line = |%s|\n", line);
		i = 0;
		if (*line == '<' || *line == '>')
		{
//			printf("line = %c\n", *line);
//			printf("aqui\n");
			line += len_redir(line);
		}
		if (!(*line == '<' || *line == '>') && ++i)
		{
			while (!(*line == '<' || *line == '>'))
				line++;
		}
	}
	return (i);
}

char	**ft_split_redir(char *line)
{
	char	**m;
	int		i;
	int		j;

//	printf("aqui\n");
//	printf("count = %d\n", count_redir(line));
//	printf("aqui\n");
	m = (char **)malloc(sizeof(char *) * (count_redir(line) + 1));
	j = 0;
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			m[++j] = ft_substr(line, 0, len_redir(line));
			line += len_redir(line);
		}
		else
		{
			i = 0;
			while (!(*line == '<' || *line == '>') && ++i)
				line++;
			m[++j] = ft_substr(line, 0, i);
			line += i;
		}
	}
	m[++j] = NULL;
	return (m);
}
