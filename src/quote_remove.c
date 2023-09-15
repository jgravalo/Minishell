#include "../inc/minishell.h"

int count_quotes(t_shell *shell, char *str)
{	
	int count;
	int i;
	t_quote	*ptr;

	i = 0;
	count = 0;
	ptr = shell->quote;
	//printf("str es %s\n", str);
	while (str[i])
	{
		if (i == ptr->start)
		{
			count += 2;
			i++;
			while (i != ptr->end)
				i++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

void copy_new(t_shell *shell, char *new, char *str)
{
	int i;
	int j;
	t_quote *ptr;

	i = 0;
	j = 0;
	ptr = shell->quote;
	while (str[i])
	{
		if (i == ptr->start - ptr->start)
		{
			i++;
			while(i != ptr->end - ptr->start)
				new[j++] = str[i++];
			i++;
		}
		else
			new[j++] = str[i++];
	}
	new[j] = '\0';
}

char *remove_quotes(t_shell *shell, char *str)
{
	char *tmp;
	int	len;

	len = count_quotes(shell, str);
	//printf("quotes to remove %d\n", len);
	tmp = malloc(sizeof (char) * ft_strlen(str) - len + 1);
	copy_new(shell, tmp, str);
	//printf("after remove quote %s\n", tmp);
	free(str);
	return (tmp);
}

/* static void redir_remove(t_cmd **cmd)
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
			r_ptr = r_ptr->next;
		}
		i++;
	}	
}
 */
/* static void arg_remove(t_cmd **cmd)
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
				printf("quotes son %d\n", len);
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
} */