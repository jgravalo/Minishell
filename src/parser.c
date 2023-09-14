#include "../inc/minishell.h"

static int count_pipes(t_shell *shell, t_tok *tokens)
{	
	int count;

	count = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->type, "PIPE") == 0)
			count++;
		tokens = tokens->next;
	}
	shell->pipes = count;
	return (count);
}

static int redir_type(t_tok *token)
{
	if (ft_strcmp(token->token, "<") == 0)
		return (IN);
	if (ft_strcmp(token->token, ">") == 0)
		return (OUT);
	if (ft_strcmp(token->token, ">>") == 0)
		return (APPEND);
	if (ft_strcmp(token->token, "<<") == 0)
		return (HERE);
}

static void init(t_cmd **cmd, int n)
{	
	int i;

	i = 0;
	while (i < n)
	{	
		cmd[i] = malloc(sizeof (t_cmd));
		cmd[i]->redir_list = NULL;
		cmd[i]->redir_x = NULL;
		cmd[i]->arg = NULL;
		cmd[i]->argx = NULL;
		cmd[i]->builtin = 0;
		i++;
	}
	cmd[i] = NULL;
}

static void parse(t_tok *tokens, t_cmd **cmd)
{
	
	int j;
	int redir;

	j = 0;
	redir = 0;
	while (tokens)
	{
		if (ft_strcmp(tokens->type, "WORD") == 0)			// si es palabra, para la lista de argumentos
			ft_arglstadd_back(&(cmd[j]->arg), ft_arglstnew(ft_strdup(tokens->token)));
		else if (ft_strcmp(tokens->type, "REDIR") == 0)
		{	
			printf("se crea nodo redir\n");
			redir = redir_type(tokens);						//si es redir, guardamos el tipo
			tokens = tokens->next;
			ft_redirlstadd_back(&(cmd[j]->redir_list), ft_redirlstnew(redir)); // y creamos nodo con el tipo, como en funcion
			ft_arglstadd_back(&(ft_redirlstlast(cmd[j]->redir_list)->path_arg), ft_arglstnew(tokens->token));
			// y en esta ultima linea, vamos a buscar al ultimo nodo de redir, y anadimos al fondo de la lista un nodo de arg,
			// con el texto del token que tocara, es decir, el path del file
		}
		else //si encontramos pipe, vamos a una nueva estructura de comando
			j++;
		tokens = tokens->next;
	}
	j++;
	cmd[j] = NULL;
}


void parser(t_shell *shell)
{	
	int n;

	n = count_pipes(shell, shell->tokens);   // el numero de pipes marca cuantas estructuras de comandos.
	shell->s_cmd = malloc(sizeof (t_cmd *) * (n + 2)); // si es n = 0, seguiremos necesitando uno + el nulo
	init(shell->s_cmd, n + 1); 
	parse(shell->tokens, shell->s_cmd);
}