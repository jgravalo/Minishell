#include "../inc/minishell.h"

char	*search_quote(char *s)
{
	char	*c;
	char	*tmp;

	c = readline("> ");
//	printf("c = |%s|\n", c);
	tmp = ft_strdup("\n");
	if (ft_strcmp(c, "") != 0)
		tmp = ft_strjoin("\n", c);
//	printf("tmp = %s\n", tmp);
	free(c);
	c = ft_strjoin(s, tmp);
//	printf("c = %s\n", c);
	free(tmp);
	free(s);
	return (parse_quotes(c));
}

char	*parse_quotes(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (/*(type == 0 || type == 1) &&*/ s[i] &&
				!(s[i - 1] != '\\' && s[i] == '\"') && ++i)
		if (/*(type == 0 || type == 1) &&*/ s[i] &&
				!(s[i - 1] != '\\' && s[i] == '\'') && ++i)
		{
			while (s[i] && !(s[i - 1] != '\\' && s[i] == '\''))
				j++;
			if (!s[i])
				return (search_quote(s));
//				return (NULL);
		}
		i++;
	}
	return (s);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	char *c = parse_quotes(ft_strdup(argv[1]));
	printf("c = %s\n", c);
	free(c);
	return (0);
}
