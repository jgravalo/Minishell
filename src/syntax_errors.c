/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:23:10 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/10 09:52:12 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

int	quote_error(char quote)
{
	ft_printf(2, "bash: syntax error near unexpected token `%c\'\n", quote);
	return (258);
}

int	parse_quotes(t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	if (!ft_strchr(shell->readline, '\'')
		&& !ft_strchr(shell->readline, '\"'))
		return (0);
	while (shell->readline[i])
	{
		if (shell->readline[i] == '\'' || shell->readline[i] == '\"')
		{
			quote = shell->readline[i];
			i++;
			while (shell->readline[i] && shell->readline[i] != quote)
				i++;
			if (!shell->readline[i])
				return (quote_error(quote));
		}
		i++;
	}
	return (0);
}

int	quotes_errors(t_shell *sh)
{
	if (parse_quotes(sh) != 0)
	{
		sh->exit = 258;
		add_history(sh->readline);
		return (258);
	}
	return (0);
}
