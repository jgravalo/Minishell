#include  "../inc/minishell.h"

static char *get_var(char *str, int *j)
{
	int i;
	int start;

	i = 0;
	(*j)++;
	start = *j;
	while (str[*j] && is_alpha_num(str[*j]) && str[*j] != ' ' && str[*j] != '$' && str[*j] != '\"' && str[*j] != '\'')
	{	
		(*j)++;
		i++;
	}
	return (ft_substr(str, start, i));
}

static void check_single(char *str, int *i, int *j, t_shell *shell)
{	
	int start;
	int end;


	if (str[*j] == '\'')
	{	
		start = *i;
		shell->tmp_tok[(*i)++] = str[(*j)++];
		while (str[*j] != '\'')
			shell->tmp_tok[(*i)++] = str[(*j)++];
		shell->tmp_tok[(*i)++] = str[(*j)++];
		end = *i - 1;
		ft_quotelstadd_back(&shell->quote, ft_quotelstnew(start, end));
		//printf("quote struct added, start %d. end %d\n", start, end);
	}
}

static int check_double(char *str, int *i, int *j, t_shell *shell)
{	
	char *var;
	char *exp;
	int start;
	int end;
	int	m;

	if (str[*j] == '\"')
	{	
		start = *i;
		shell->tmp_tok[(*i)++] = str[(*j)++];
		while (str[*j] != '\"')
		{	
			m = 0;
			if (str[*j] == '$' && is_alpha_num_exp(str[(*j) + 1]) == 1)
			{	
				var	=	get_var(str, j);
				if (ft_strcmp(var, "?") == 0)
					exp = ft_itoa(shell->exit);
				else
					exp = ft_strdup(search_var_line(var, shell->envp));
				while (exp && exp[m])
					shell->tmp_tok[(*i)++] = exp[m++];
			}
			else
				shell->tmp_tok[(*i)++] = str[(*j)++];
		}
		shell->tmp_tok[(*i)++] = str[(*j)++];
		end = *i - 1;
		ft_quotelstadd_back(&shell->quote, ft_quotelstnew(start, end));
	//	printf("quote struct added, start %d. end %d\n", start, end);
	}
}

static void check_normal(char *str, int *i, int *j, t_shell *shell)
{	
	char *var;
	char *exp;
	int m;

	while (str[*j] && str[*j] != '\'' && str[*j] != '\"')
	{	
		m = 0;
		if (str[*j] == '$' && is_alpha_num_exp(str[*j + 1]) == 1)
		{
			var	=	get_var(str, j);
			if (ft_strcmp(var, "?") == 0)
				exp = ft_itoa(shell->exit);
			else
				exp = ft_strdup(search_var_line(var, shell->envp));
			//printf("exp is %s\n", exp);
			while (exp && exp[m])
				shell->tmp_tok[(*i)++] = exp[m++];
		}
		else if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
			(*j)++;	
		else
			shell->tmp_tok[(*i)++] = str[(*j)++];
	}
}

static void	expand(t_shell *shell, char *str, int *j)
{
	int i;

	i = 0;
	while (str[*j])
	{
		check_single(str, &i, j, shell);
		check_double(str, &i, j, shell);
		check_normal(str, &i, j, shell);
	}
	shell->tmp_tok[i] = '\0';
}

char *expand_str(t_shell *shell, t_arg *arg, int *i, int *j)
{
	int len;

	len = count_expstr(shell, arg->arg, i);
	//printf("len is %d\n", len);
	if (len > 0)
	{
		shell->tmp_tok = malloc(sizeof (char) * len + 1);
		expand(shell, arg->arg, j);
	}
	else
		shell->tmp_tok = NULL;
	return (shell->tmp_tok);
}