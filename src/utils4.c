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
		ft_printarglist(cmd[i]->arg);
		ft_printredirlist(cmd[i]->redir_list);
		i++;
	}
}

void	ft_printredirlist(t_redir *redir)
{
	while (redir)
	{
		printf("redir type %d\n", redir->type);
		ft_printredirarglist(redir->path_arg);
		redir = redir->next;
	}
}

void	ft_printredirarglist(t_arg *arg)
{
	while (arg)
	{
		printf("redir path %s\n", arg->arg);
		arg = arg->next;
	}
}

void	ft_printarglist(t_arg *arg)
{
	while (arg)
	{
		printf("arg %s\n", arg->arg);
		arg = arg->next;
	}
}