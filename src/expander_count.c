#include  "../inc/minishell.h"

static char *get_var(char *str, int *i)
{
	int j;
	int start;

	j = 0;
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
	{	
		(*i)++;
		j++;
	}
	return (ft_substr(str, start, j));
}

static int check_single(char *str, int *count, int *i)
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
		return (1);
	}
	return (0);
}

static int check_double(char *str, int *count, int *i, char **envp)
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
				var	=	get_var(str, i);
				if (ft_strcmp(var, "?") == 0)
					(*count)++;
				else
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
		return (1);
	}
	return (0);
}

static void check_normal(char *str, int *count, int *i, char **envp)
{	
	char *var;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{	
		if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
		{	
			var	=	get_var(str, i);
			if (ft_strcmp(var, "?") == 0)
				(*count)++;
			else
				(*count) +=	ft_strlen(search_var_line(var, envp));
		}
		else
		{	
			(*i)++;
			(*count)++;
		}
	}
}

int count_expstr(t_shell *shell, char *str, int *quotes)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{	
		if (check_single(str, &count, &i))
			*quotes = 1;
		if (check_double(str, &count, &i, shell->envp))
			*quotes = 1;
		check_normal(str, &count, &i, shell->envp);
	}
	return (count);
}
