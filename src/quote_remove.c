#include "../inc/minishell.h"

static int count_quotes(char *str)
{	
	int count;
	char quote;

	count = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			count += 2;
			str++;
			while (*str != quote)
				str++;
			str++;
		}
		else
			str++;
	}
	return (count);
}

static void copy_new(char *new, char *str)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while(quote != str[i])
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
}

static void redir_remove(t_cmd **cmd)
{
	int len;
	int i;
	char *tmp;

	i = 0;
	len = 0;
	while (cmd[i])
	{	
		while (cmd[i]->redir_x)
		{	
			while(cmd[i]->redir_x->path_arg)
			{
				len = count_quotes(cmd[i]->redir_x->path_arg->arg);
				if (len > 0)
				{
					tmp = malloc(sizeof (char) * ft_strlen(cmd[i]->redir_x->path_arg->arg) - len + 1);
					copy_new(tmp, cmd[i]->redir_x->path_arg->arg);
					free(cmd[i]->redir_x->path_arg->arg);
					cmd[i]->redir_x->path_arg->arg = ft_strdup(tmp);
					free(tmp);
				}
				cmd[i]->redir_x->path_arg = cmd[i]->redir_x->path_arg->next;
			}
			cmd[i]->redir_x = cmd[i]->redir_x->next;
		}
		i++;
	}	
}

static void arg_remove(t_cmd **cmd)
{
	int len;
	int i;
	char *tmp;

	i = 0;
	len = 0;
	while (cmd[i])
	{	
		while (cmd[i]->argx)
		{	
			len = count_quotes(cmd[i]->argx->arg);
			if (len > 0)
			{
				tmp = malloc(sizeof (char) * ft_strlen(cmd[i]->argx->arg) - len + 1);
				copy_new(tmp, cmd[i]->argx->arg);
				free(cmd[i]->argx->arg);
				cmd[i]->argx->arg = ft_strdup(tmp);
				free(tmp);
			}
			cmd[i]->argx = cmd[i]->argx->next;
		}
		i++;
	}
}

void quote_remove(t_cmd **cmd)
{	
	arg_remove(cmd);
	redir_remove(cmd);
}