/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:58 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/19 19:17:40 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

static void	copy_token(char *dst, const char *src, int *cpy, size_t dstsize)
{
	int	i;

	i = 0;
	while (i < ((int) dstsize - 1))
	{
		dst[i] = src[*cpy];
		++i;
		(*cpy)++;
	}
	dst[i] = '\0';
}

static void	init_lex_variables(int *i, int *len, int *cpy, int *size)
{
	*i = 0;
	*len = 0;
	*cpy = 0;
	*size = 0;
}

static void	lexer_loop(char *line, t_shell *sh, int n)
{
	int	i;
	int	len;
	int	cpy;
	int	size;

	init_lex_variables(&i, &len, &cpy, &size);
	while (i < n)
	{
		while (is_space(line[len]))
		{
			len++;
			cpy++;
		}
		size = get_len(line, &len) + 1;
		sh->tmp = (char *)malloc(sizeof (char) * size);
		check_malloc_error(sh->tmp);
		copy_token(sh->tmp, line, &cpy, size);
		tokback(&(sh->tok), toknew(ft_strdup(sh->tmp)));
		free(sh->tmp);
		i++;
	}
}

void	lexer(t_shell *sh, char *line)
{
	int		n;

	sh->tok = NULL;
	n = count_tokens(line);
	lexer_loop(line, sh, n);
}
