/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:11 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 14:15:26 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_pipes(t_shell *sh, t_tok *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "PIPE") == 0)
			count++;
		tok = tok->next;
	}
	sh->pipes = count;
	return (count);
}

static int	redir_type(t_tok *tok)
{
	if (ft_strcmp(tok->tok, "<") == 0)
		return (IN);
	if (ft_strcmp(tok->tok, ">") == 0)
		return (OUT);
	if (ft_strcmp(tok->tok, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(tok->tok, "<<") == 0)
		return (HERE);
}

static void	init(t_cmd **cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmd[i] = malloc(sizeof (t_cmd));
		cmd[i]->red = NULL;
		cmd[i]->red_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->arg_x = NULL;
		cmd[i]->args = NULL;
		cmd[i]->builtin = 0;
		i++;
	}
	cmd[i] = NULL;
}

static void	parse(t_tok *tok, t_cmd **cmd)
{
	int	j;
	int	redir;

	j = 0;
	redir = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "WORD") == 0)			// si es palabra, para la lista de argumentos
			argback(&(cmd[j]->arg), argnew(ft_strdup(tok->tok)));
		else if (ft_strcmp(tok->type, "REDIR") == 0)
		{	
			redir = redir_type(tok);						//si es redir, guardamos el tipo
			tok = tok->next;
			redirback(&(cmd[j]->red), redirnew(redir)); // y creamos nodo con el tipo, como en funcion
			argback(&(redirlast(cmd[j]->red)->arg), argnew(tok->tok));
			// y en esta ultima linea, vamos a buscar al ultimo nodo de redir, y anadimos al fondo de la lista un nodo de arg,
			// con el texto del token que tocara, es decir, el path del file
		}
		else //si encontramos pipe, vamos a una nueva estructura de comando
			j++;
		tok = tok->next;
	}
	j++;
	cmd[j] = NULL;
}

void	parser(t_shell *sh)
{
	int	n;

	n = count_pipes(sh, sh->tok);   // el numero de pipes marca cuantas estructuras de comandos. (n + 1)
	sh->s_cmd = malloc(sizeof (t_cmd *) * (n + 2)); // si es n = 0, seguiremos necesitando uno + el nulo
	init(sh->s_cmd, n + 1); 
	parse(sh->tok, sh->s_cmd);
}
