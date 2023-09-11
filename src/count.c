/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:04 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/08 16:23:56 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_ascii(char *line, int c)
{
	int	i;
	int	count;
	char quote;

	quote = 0;
	i = 0;
	count = 0;
//	printf("line = <%s>\n", line);
	while (line[i])
	{	
//	printf("aqui\n");
		if (line[i] == '\'' || line[i] == '\"')
		{	
			quote = line[i];
			i++;
			while (line[i] != quote)
				i++;
		}
		else if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	count_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

char	*modify_line(char *args, char **vars, int len)
{
	int		i;
	int		j;
	int		n;
	char	*new;

	i = 0;
	j = 0;
	n = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(args) + len));
	while (args[i])
	{
		if (args[i] && args[i - 1] == '\'')
		{
			while (args[i] != '\'')
			{
				new[n] = args[i];
				i++;
				n++;
			}
			new[n] = args[i];
			i++;
			n++;
		}
		if (args[i - 1] == '$')
		{
			while (args[i] && ((args[i] > '0' && args[i] < '9') 
					|| (args[i] > 'A' && args[i] < 'Z') 
					|| (args[i] > 'a' && args[i] < 'z')))
				i++;
			ft_strcat(new, vars[j]);
			n += ft_strlen(vars[j]);
			j++;
		}
		if (args[i] != '$')
			new[n] = args[i];
		i++;
		n++;
	}
	return (new);
}

char	*check_vars(char *args, char **envp)
{
	int		i;
	int		j;
	int		start;
	char	*name;
//	char	*var;

	i = 0;
	j = 0;
	char	**vars = (char **)malloc(sizeof(char *) * count_ascii(args, '$'));
//	int		vars = count_ascii(args, '$');
//	printf("vars = %d\n", vars);
//	printf("i[%d] = |%c|\n", 17, args[17]);
	while (args[i])
	{
//		write(1, "aqui ", 5);
//		printf("i[%d] = |%c|\n", i, args[i]);
		if (args[i] && args[i - 1] == '\'')
		{
			while (args[i] != '\'')
				i++;
			i++;
		}
		if (args[i - 1] == '$')
		{
			start = i;
			while (args[i] && ((args[i] > '0' && args[i] < '9') 
					|| (args[i] > 'A' && args[i] < 'Z') 
					|| (args[i] > 'a' && args[i] < 'z')))
			{
				i++;
			}
			name = ft_substr(args, start, i - start);
//			write(1, "var = ", 6);
//			write(1, name, ft_strlen(name));
//			write(1, "\n", 1);
//			var = search_var(name, envp);
			vars[j++] = search_var_line(name, envp);
//			write(1, "new = ", 6);
//			write(1, var, ft_strlen(vars));
//			write(1, "\n", 1);
			free(name);
		}
		i++;
	}
	i = 0;

	int len;
	len = 0;
	while (vars[i])
	{
//		printf("vars[i] = %s\n", vars[i]);
		len += ft_strlen(vars[i]);
		i++;
	}

//			write(1, "old = ", 6);
//			write(1, args, ft_strlen(args));
//			write(1, "\n", 1);
	args = modify_line(args, vars, len);
//			write(1, "new = ", 6);
//			write(1, args, ft_strlen(args));
//			write(1, "\n", 1);
	return (args);
}
