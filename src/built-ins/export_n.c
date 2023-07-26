#include "../../inc/minishell.h"

static int	parse_var(char *var)
{
	int i;

	i = 0;
	if (is_digit(var[i]) == 1 || is_alpha(var[i]) == 0)
		return (1);
	i++;
	while(var[i])
	{	
		if (var[i] == '=')
			return (0);
		if (is_alpha_num(var[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int write_not_valid(char *var)
{
	write(2, "bash: export: `", 15);
	write(2, var, ft_strlen(var));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

static int replace_existing(char *line, char *existing, t_shell *shell)
{	
	char **new;
	int i;
	char *var;

	printf("entra en replace\n");
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_substr(line, 0, i);
	printf("var is %s\n", var);
	i = 0;
	new = (char **)malloc(sizeof(char *) * (count_arr(shell->envp) + 1));
	if (!new)
		return (1);
	while (shell->envp[i] != NULL)
	{	
		if (ft_varcmp(var, shell->envp[i], ft_strlen(var)) == 0)
			new[i] = ft_strdup(line);
		else
			new[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new[i] = NULL;
	free(shell->envp);
	shell->envp = new;
	return (0);
}

static int add_envp(char *var, t_shell *shell)
{
	char	**new;
	int		i;

	printf("entra en add\n");
	new = (char **)malloc(sizeof(char *) * (count_arr(shell->envp) + 2));
	if (!new)
		return (1);
	i = 0;
	while (shell->envp[i] != NULL)
	{	
		new[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	i++;
	new[i] = NULL;
	free(shell->envp);
	shell->envp = new;
	return (0);
}

int export_n(char *var, t_shell *shell)
{
	char	**new;
	char *existing;
	int		i;

	if (parse_var(var) == 1)
		return (write_not_valid(var));
	if (is_existing(var, shell->envp) == 1)
		return (replace_existing(var, existing, shell));
	else
		return (add_envp(var, shell));
}