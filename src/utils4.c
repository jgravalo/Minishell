#include "../inc/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((s1[i] != '\0') || (s2[i] != '\0')) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	i++;
	}
	return (0);
}

int	ft_varcmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	i++;
	}
	if (s2[i] == '+' || s2[i] == '=' || s2[i] == '\0')
		return (0);
	else
		return (-1);
}

void	ft_print_intarr(int *arr, int n)
{
	int i;

	i = 0;
	while (n)
	{
		printf("%d", arr[i]);
		i++;
		n--;
	}
	printf("\n");
}

void	ft_printcmd(t_cmd **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		printf("args son:\n");
		ft_printarr(cmd[i]->args);
		ft_printredirlist(cmd[i]->redir_list);
		i++;
	}
}

void	ft_printredirlist(t_redir *redir)
{
	while (redir)
	{
		printf("type %d, path %s\n", redir->type, redir->path);
		redir = redir->next;
	}
}