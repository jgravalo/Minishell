#include  "../inc/minishell.h"

static char *get_var(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (ft_substr(str, 0, i));
}

static void check_single(char *str, int *count, int *i)
{
	if (str[*i] == '\'')
	{	
		(*i)++;
		(*count)++;
		while (str[*i] != '\'')
		{	
			(*i)++;
			(*count)++;
		}
		(*i)++;
		(*count)++;
	}
}

static void check_double(char *str, int *count, int *i, char **envp)
{	
	char *var;

	if (str[*i] == '\"')
	{	
		(*i)++;
		(*count)++;
		while (str[*i] != '\"')
		{
			if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
			{	
				var	=	get_var(&str[*i]);
				(*count) +=	ft_strlen(search_var_line(var, envp));
			}
			else
			{
				(*i)++;
				(*count)++;
			}
		}
		(*i)++;
		(*count)++;
	}
}

static void check_normal(char *str, int *count, int *i)
{
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		(*i)++;
		(*count)++;
	}
}

static int count_expstr(t_shell *shell, char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{	
		check_single(&str[i], &count, &i);
		check_double(&str[i], &count, &i, shell->envp);
		check_normal(&str[i], &count, &i);
	}
	return (count);
}

char *expand_str(t_shell *shell, t_tok *node)
{
	int len;
	char *exp;
	int i;

	i = 0;
	len = count_expstr(shell, node->token);
	printf("len is %d\n", len);
	exp = malloc(sizeof (char) * len + 1);
	while (node->token[i])
	{
		if ()
	}
}