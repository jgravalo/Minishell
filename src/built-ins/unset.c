int unset(char *var, char **envp)
{
	char	**new;
	int		i;
	int		j;
	int		n;

	n = search_var_num(var, envp);
	if (n < 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(envp));
	i = 1;
	j = 0;
	while (envp[i + j])
	{
		if (i != n)
			j++;
		new[i] = envp[i + j];
		i++;
	}
	return (0);
}
