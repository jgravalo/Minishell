#include "../inc/minishell.h"

static char	*search_quote(char *s, char c)
{
	char	*line;
	char	*tmp;
	int 	quote;

	quote = 0;
	while (quote == 0)
	{	
		line = readline("> ");
		if (ft_strchr(line, c) != NULL)  // si se ha introducido las comillas que cierran, saldremos del loop
			quote = 1;
		tmp = ft_strdup("\n");
		if (ft_strcmp(line, "") != 0)
			tmp = ft_strjoin("\n", line);
		free(line);
		line = ft_strjoin(s, tmp);
		free(tmp);
		free(s);
	}
	return (line);
}

static int detect_first_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}

char	*parse_quotes(char *s)
{
	int		i;
	int		quote;

	i = 0;
	if (ft_strchr(s, '\"') == 0 && ft_strchr(s, '\'') == 0)  // si no hay comillas en readline, fuera
		return (s);
	while (s[i])
	{	
		quote = 0;
		//entiendo que bash comprueba la primera quotes que encuentra, la primera sin cerrar es la que manda
		while (quote == 0)  							
			quote = detect_first_quote(s[i++]);
		/* if ((type == 0 || type == 1) && s[i] &&
				!(s[i - 1] != '\\' && s[i] == '\'') && ++i) */
		if (quote == 1) // simplificaría condiciones
		{	
			printf("entra en \' loop\n");
			while (s[i] && !(s[i - 1] != '\\' && s[i] == '\''))
				i++;
			if (!s[i])
				return (search_quote(s, '\''));
		}
		/* if ((type == 0 || type == 1) && s[i] &&
				!(s[i - 1] != '\\' && s[i] == '\"') && ++i) */
		if (quote == 2)   // simplificaría condiciones
		{	
			printf("entra en \" loop\n");
			while (s[i] && !(s[i - 1] != '\\' && s[i] == '\"'))
				i++;
			if (!s[i])
				return (search_quote(s, '\"'));
		}
		i++;
	}
	return (s);
}

/* int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	char *c = parse_quotes(ft_strdup(argv[1]));
	printf("c = %s\n", c);
	free(c);
	return (0);
} */
