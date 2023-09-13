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

void quote_remove(t_tok *expanded)
{	
	int len;
	char *new;

	len = 0;
	while (expanded)
	{	
		len = count_quotes(expanded->token);
		printf("len es %d\n", len);
		if (len > 0)
		{
			new = malloc(sizeof (char) * ft_strlen(expanded->token) - 2 + 1);
			copy_new(new, expanded->token);
			free(expanded->token);
			expanded->token = new;
		}
		expanded = expanded->next;
	}
}