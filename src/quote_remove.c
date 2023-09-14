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
	t_arg *ptr;
	t_redir *r_ptr;

	i = 0;
	len = 0;
	while (cmd[i])
	{	
		r_ptr = cmd[i]->redir_x;
		while (r_ptr)
		{	
			ptr = r_ptr->path_arg;
			while(ptr)
			{	
				printf("arg es %s\n", ptr->arg);
				if (ptr->quoted)
				{
					len = count_quotes(ptr->arg);
					printf("len is %d\n", len);
					if (len > 0)
					{
						tmp = malloc(sizeof (char) * ft_strlen(ptr->arg) - len + 1);
						copy_new(tmp, ptr->arg);
						free(ptr->arg);
						ptr->arg = ft_strdup(tmp);
						free(tmp);
					}
				}
				ptr = ptr->next;
			}
			r_ptr = r_ptr->next;
		}
		i++;
	}	
}

static void arg_remove(t_cmd **cmd)
{
	int len;
	int i;
	char *tmp;
	t_arg *ptr;

	i = 0;
	len = 0;
	while (cmd[i])
	{	
		ptr = cmd[i]->argx;
		while (ptr)
		{	
			if (ptr->quoted)
			{
				len = count_quotes(ptr->arg);
				if (len > 0)
				{
					tmp = malloc(sizeof (char) * ft_strlen(ptr->arg) - len + 1);
					copy_new(tmp, ptr->arg);
					free(ptr->arg);
					ptr->arg = ft_strdup(tmp);
					free(tmp);
				}
			}
			ptr = ptr->next;
		}
		i++;
	}
}

void quote_remove(t_cmd **cmd)
{	
	arg_remove(cmd);
	redir_remove(cmd);
}