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

static void check_single(char *str, int *i, int *j, t_shell *shell)
{
	if (str[*i] == '\'')
	{	
		shell->tmp_tok[(*j)++] = str[(*i)++];
		while (str[*i] != '\'')
			shell->tmp_tok[(*j)++] = str[(*i)++];
		shell->tmp_tok[(*j)++] = str[(*i)++];
	}
}

static void check_double(char *str, int *i, int *j, t_shell *shell)
{	
	char *var;
	char *exp;
	int	m;

	if (str[*i] == '\"')
	{	
		shell->tmp_tok[(*j)++] = str[(*i)++];
		while (str[*i] != '\"')
		{	
			m = 0;
			if (str[*i] == '$' && is_alpha_num_exp(str[(*i) + 1]) == 1)
			{	
				var	=	get_var(str, i);
				if (ft_strcmp(var, "?") == 0)
					exp = ft_itoa(shell->exit);
				else
					exp = ft_strdup(search_var_line(var, shell->envp));
				while (exp && exp[m])
					shell->tmp_tok[(*j)++] = exp[m++];
			}
			else
				shell->tmp_tok[(*j)++] = str[(*i)++];
		}
		shell->tmp_tok[(*j)++] = str[(*i)++];
	}
}

static void check_normal(char *str, int *i, int *j, t_shell *shell)
{	
	char *var;
	char *exp;
	int m;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{	
		m = 0;
		if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
		{
			var	=	get_var(str, i);
			if (ft_strcmp(var, "?") == 0)
				exp = ft_itoa(shell->exit);
			else
				exp = ft_strdup(search_var_line(var, shell->envp));
			while (exp[m])
				shell->tmp_tok[(*j)++] = exp[m++];
		}
		else
			shell->tmp_tok[(*j)++] = str[(*i)++];
	}
}

static void	expand(t_shell *shell, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{	
		check_single(str, &i, &j, shell);
		check_double(str, &i, &j, shell);
		check_normal(str, &i, &j, shell);
	}
	shell->tmp_tok[j] = '\0';
}

char *expand_str(t_shell *shell, t_tok *node)
{
	int len;

	len = count_expstr(shell, node->token);
	//printf("len es %d\n", len);
	if (len > 0)
	{
		shell->tmp_tok = malloc(sizeof (char) * len + 1);
		expand(shell, node->token);
	}
	else
		shell->tmp_tok = NULL;
	//printf("linea expandida es %s\n", shell->tmp_tok);
	return (shell->tmp_tok);
}