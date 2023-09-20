/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reviser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:23:44 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:00 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	sintax_error(char *s)
{
	write(2, "bash: syntax error near expected token `", 41);
	write(2, s, ft_strlen(s));
	write(2, "\'\n", 2);
	return (258);
}

int	search_pipe(t_shell *sh)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

//	printf("readline before = <%s>\n", shell->readline);
	line = "";
	while (ft_strcmp(line, "") == 0)
		line = readline("> ");
	tmp = ft_strjoin(" ", line);
	tmp2 = ft_strjoin(sh->readline, tmp);
	free(line);
	free(sh->readline);
	sh->readline = tmp2;
	free(tmp);
//	printf("readline after = <%s>\n", shell->readline);
	tokclear(&sh->tok);
	lexer(sh, sh->readline);
    categorizer(sh->tok);
	if (reviser(sh->tok, sh) != 0)
		return (258);
	return (0);
}

int	reviser_loop(t_tok *tok, int *redir, int *pipe)
{
	while (tok)
	{
		if (tok && ft_strcmp(tok->type, "REDIR") == 0)
		{
			if (*redir == 1)
				return (sintax_error(tok->tok));
			*redir = 1;
		}
		if (tok && ft_strcmp(tok->type, "WORD") == 0)
		{
			*pipe = 0;
			*redir = 0;
		}
		if (tok && ft_strcmp(tok->type, "PIPE") == 0)
		{
			if (*pipe == 1 || *redir == 1)
				return (sintax_error(tok->tok));
			*pipe = 1;
		}
		tok = tok->next;
	}
	return (0);
}

int	reviser(t_tok *tok, t_shell *sh)
{
	int pipe;
	int redir;
	
	redir = 0;
	pipe = 1;

	if (reviser_loop(tok, &redir, &pipe) != 0)
		return (258);
	if (redir == 1)
		return (sintax_error("newline"));
	if (pipe == 1)
		if (search_pipe(sh) != 0)
			return (258);
	return (0);
}
