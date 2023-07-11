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

	i = 0;
	if ((*line == '>' || *line == '<') && ++i)
		line++;
	if ((*line == '>' || *line == '<') && ++i)
		line++;
	while (*line && *line == ' ' && ++i)
		line++;
	while (*line && *line != ' ' && ++i)
		line++;
	while (*line && *line == ' ' && ++i)
		line++;
	return (i);
}

int		count_redir(char *line)
{
	int i;

	i = 0;
	while (*line != '\0')
	{
		if ((*line == '<' || *line == '>') && ++i)
			line += len_redir(line);
		if (*line && *line != '<' && *line != '>' && ++i)
			while (*line && *line != '<' && *line != '>')
				line++;
	}
	return (i);
}

char	**ft_split_redir(char *line)
{
	char	**m;
	int		i;
	int		j;
	int len;

//	printf("count = %d\n", count_redir(line));
//	printf("aqui\n");
	m = (char **)malloc(sizeof(char *) * (count_redir(line) + 1));
	j = -1;
	while (*line)
	{
		if (*line == '<' || *line == '>')
		{
			len = len_redir(line);
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

int	make_redir(char *line)
{
	char **tmp;
	int fd;

	tmp = ft_split_marks(line, ' ');
	printf("tmp[1] = %s\n", tmp[1]);
	if (ft_strcmp(tmp[0], "<") == 0)
		fd = open(tmp[1], O_RDONLY);
	if (ft_strcmp(tmp[0], ">") == 0)
		fd = open(tmp[1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (ft_strcmp(tmp[0], ">>") == 0)
		fd = open(tmp[1], O_RDWR | O_CREAT | O_APPEND, 00644);
	if (line[0] == '>')
		dup2(fd, 1);
	else if (line[0] == '<')
		dup2(fd, 0);
	free(tmp);
	return (fd);
}

char *parse_redir(char *line)
{
	char **args;
	char *cmd;
	char *c;
	int i;

	cmd = ft_strdup("");
	args = ft_split_redir(line);
//	printf("aqui\n");
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>')
		{
			make_redir(args[i]);
//			printf("args[%d] = |%s|\n", i, args[i]);
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
	return (cmd);
}
/*
int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	//
	printf("len = %d\n", len_redir(argv[1]));
	printf("count = %d\n", count_redir(argv[1]));
	char **m = ft_split_redir(argv[1]);
	int i;
	for (i = 0; m[i]; i++)
		printf("m[%d] = |%s|\n", i, m[i]);
	//
	char *cmd = parse_redir(argv[1]);
	printf("cmd = |%s|\n", cmd);
	return (0);
}*/
