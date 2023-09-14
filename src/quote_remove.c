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

void quote_remove(t_cmd **cmd)
{	
	int len;
	int i;
	char *tmp;

	i = 0;
	len = 0;
	while (cmd[i])
	{	
		cmd[i]->arg = NULL;
		while (cmd[i]->argx)
		{	
			len = count_quotes(cmd[i]->argx->arg);
			if (len > 0)
			{
				tmp = malloc(sizeof (char) * ft_strlen(cmd[i]->argx->arg) - len + 1);
				copy_new(tmp, cmd[i]->argx->arg);
				printf("pasa de aqui\n");
				ft_arglstadd_back(&(cmd[i]->arg), ft_arglstnew(ft_strdup(tmp)));
			}
			else
				ft_arglstadd_back(&(cmd[i]->arg), ft_arglstnew(ft_strdup(cmd[i]->argx->arg)));
			cmd[i]->argx = cmd[i]->argx->next;
		}
		i++;
	}
}