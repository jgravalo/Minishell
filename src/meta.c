/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:38:46 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/12 02:28:06 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_split_meta(char const *s, char c)
{
	int		j;
	int		i;
	char	**res;

	res = (char **) malloc((words_meta(s, c) * (sizeof(char *))) + 8);
	if (!res || !s)
		return (0);
	j = 0;
	while (*s)
	{	
		s += search_dollar(s, c);
		if (*s == '\0')
			break;
		++s;
		if (*s != c)
		{
			i = 0;
			res[j++] = meta_str(s, c, &i);
			//printf("res es %s\n", res[j - 1]);
			s += i;
		}
		else
			++s;
	}
	res[j++] = NULL;
	return (res);
}

void	make_p(t_shell *shell, t_var *p, char *new_line, int n)
{
	int j;

	j = 0;
	if (p->tmp[n][j] == '?' && ++j) //exit code
		p->exp = ft_itoa(shell->exit);
	else
	{	
		if (search_var_line(p->tmp[n], shell->envp) == NULL)
		{	
			p->exp = ft_strdup("");
			j += ft_strlen(p->tmp[n]);
		}
		else
		{
			while (p->tmp[n][j] && ((p->tmp[n][j] >= 'a' && p->tmp[n][j] <= 'z')
				|| (p->tmp[n][j] >= 'A' && p->tmp[n][j] <= 'Z')
				|| (p->tmp[n][j] >= '0' && p->tmp[n][j] <= '9')
				|| (p->tmp[n][j] == '_')))
				j++;
			p->var = ft_substr(p->tmp[n], 0, j);
			p->exp = ft_strdup(search_var_line(p->var, shell->envp));
			if (p->var)
				free(p->var);
		}
	}
}

static char	*get_var(t_shell *shell, t_var *p, char *new_line, int n)
{
	int 	i;
	int start;
	char	*tmp;
	char 	*ptr;

	i = 0;
	start = 0;
	p->new = ft_strdup("");
	while (new_line[i] && p->tmp[n])
	{	
		while (new_line[i] != '$')
		{
			if (new_line[i] == '\'' && ++i)
				while (new_line[i] && new_line[i] != '\'')
					i++;
			i++;
		}
		make_p(shell, p, new_line, n);
		tmp = ft_substr(new_line, start, i - start);
		p->c = ft_strjoin(tmp, p->exp);
		if (ft_strcmp("", tmp) == 0 || ft_strcmp("", p->exp) == 0)
			p->c = ft_strdup(p->c);
//		shell->vars_exp[n] = p->exp; // guardamos la variable expandida
		free(p->exp);
		free(tmp);
		tmp = p->new;
		ptr = p->new;
///		shell->vars_loc[n][j] = get_loc_var(tmp);// guardamos la posicion de la variable expandida (ft_strlen - pipe)
		p->new = ft_strjoin(tmp, p->c);
		if (ft_strcmp("", tmp) == 0 || ft_strcmp("", p->c) == 0)
			p->new = ft_strdup(p->new);
		free(ptr);
		free(p->c);
		i += ft_strlen(p->tmp[n]) + 1;
		start = i;
		n++;
	}
	tmp = ft_substr(new_line, i, ft_strlen(new_line) - i);
	ptr = p->new;
	p->new = ft_strjoin(p->new, tmp);
	if (ft_strcmp("", p->new) == 0 || ft_strcmp("", tmp) == 0)
			p->new = ft_strdup(p->new);
	free(ptr);
	//free(tmp);
	free(new_line);
	return (p->new);
}

static char  *expand_tilde(char *line, char *new_line, t_shell *shell, t_var *p)
{	
	int i;
	int j;
	int c;
	char *tmp1;
	char *tmp2;

	if (check_for_tilde(line) == 0)
	{	
		new_line = ft_strdup(line);
		return (new_line);
	}
	else
	{	
		new_line = ft_strdup("");
		i = 0;
		j = 0;
		c = 0;
		while (line [i])
		{	
			if (line[i] == '~' && (i == 0
				&& (line[i + 1] == '\0'
				|| line[i + 1] == ' ' || line[i + 1] == '/'))
				|| (line[i - 1] == ' '
				&& (line[i + 1] == ' '
				|| line[i +1] == '\0' || line[i + 1] == '/')))
			{	
				tmp1 = ft_substr(new_line, 0, j);
				tmp2 = ft_substr(line, i - c, c);
				//free(new_line);
				new_line = ft_strjoin(tmp1, tmp2);
//				printf("line es:%s-\n", new_line);
				//free(tmp1);
				//free(tmp2);
				j = ft_strlen(new_line);
				c = 0;
				if (search_var_line("HOME", shell->envp) != NULL)
				{
					tmp1 = ft_substr(new_line, 0, j);
					new_line = ft_strjoin(tmp1, ft_strdup(search_var_line("HOME", shell->envp)));
					//free(tmp1);
				}
				else
				{
					tmp1 = ft_strjoin("/home/", shell->user);
					tmp2 = ft_substr(new_line, 0, j);
					new_line = (tmp2, tmp1);
					//free(tmp1);
					//free(tmp2);
				}
			}
			else
				c++;
			i++;
			j = ft_strlen(new_line);
		}
		if (c > 1)
		{
			tmp1 = ft_substr(line, i - c, i);
			new_line = ft_strjoin(new_line, tmp1);
			free(tmp1);
		}	
		return (new_line);
	}
}

void	init_vars(t_shell *shell, int len, char *line)
{
	int	n[len][2];
	int	i;
	int	j;

	shell->vars_exp = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (*line)
	{
		if (*line == '|')
		{
			n[i][1] = j;
			i++;
		}
		if (*line == '|')
			j++;
		line++;
	}
	shell->vars_loc = n;	
}

char	*expand_meta(t_shell *shell, char *line, int heredoc)
{
	t_var	p;
	char *new_line;

	new_line = expand_tilde(line, new_line, shell, &p);
	free(line);
	if (is_there_dollar(new_line, '$') == 0)
		return (new_line);
	//printf("detecta variable a expandir\n");
	p.tmp = ft_split_meta(new_line, '$');
	//ft_printarr(p.tmp);
//	init_vars(count_arr(p.tmp), new_line); //iniciamos guardado de posiciones de variables
	p.new = NULL;
	new_line = get_var(shell, &p, new_line, 0);
	free_m(p.tmp);
	return (new_line);
}

