/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:40:11 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 11:42:23 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_pipes(t_shell *shell, t_tok *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		if (ft_strcmp(tok->type, "PIPE") == 0)
			count++;
		tok = tok->next;
	}
	shell->pipes = count;
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
		cmd[i]->redir_list = NULL;
		cmd[i]->redir_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->argx = NULL;
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
			ft_arglstadd_back(&(cmd[j]->arg), ft_arglstnew(ft_strdup(tok->tok)));
		else if (ft_strcmp(tok->type, "REDIR") == 0)
		{	
			redir = redir_type(tok);						//si es redir, guardamos el tipo
			tok = tok->next;
			ft_redirlstadd_back(&(cmd[j]->redir_list), ft_redirlstnew(redir)); // y creamos nodo con el tipo, como en funcion
			ft_arglstadd_back(&(ft_redirlstlast(cmd[j]->redir_list)->path_arg), ft_arglstnew(tok->tok));
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

void	parser(t_shell *shell)
{
	int	n;

	n = count_pipes(shell, shell->tok);   // el numero de pipes marca cuantas estructuras de comandos. (n + 1)
	shell->s_cmd = malloc(sizeof (t_cmd *) * (n + 2)); // si es n = 0, seguiremos necesitando uno + el nulo
	init(shell->s_cmd, n + 1); 
	parse(shell->tok, shell->s_cmd);
}