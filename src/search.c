#include "../inc/minishell.h"

#include "../inc/minishell.h"

static int	get_path_env(char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	path = "PATH";
	while (envp[i])
	{
		j = 0;
		while (path[j] && envp[i][j] == path[j])
			j++;
		if (!path[j])
			return (i);
		i++;
	}
	return (-1);
}

static char	**split_paths(char *path)
{
	char	**docs;
	char	*dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

static char	*get_path(char **docs, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/' || !docs)
		return (cmd);	
	while (docs[i])
	{
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, cmd);
		if ((access(docs[i], F_OK)) != -1)
			return (docs[i]);
		i++;
	}
	free(tmp);
	return (NULL);
}

static void locate_path(t_shell *shell, t_cmd **cmd, int *i)
{	
	int env;
	char **docs;

	env = get_path_env(shell->envp);
	if (env != -1)
	{
		docs = split_paths(shell->envp[env]); // split todos los paths
		shell->tmp_tok = get_path(docs, cmd[*i]->args[0]); // lo intenta buscar
		if (!shell->tmp_tok)
			cmd_not_found(cmd[*i]->args[0]);
		cmd[*i]->path = ft_strdup(shell->tmp_tok);
		free(shell->tmp_tok);
	}
	else
		filedir_not_found(cmd[*i]->args[0]); //si no esta PATH, damos error tambien
}

void	search(t_shell *shell, t_cmd **cmd, int *i)
{
	if (ft_strchr(cmd[*i]->args[0], '/'))				//si tiene slash se considera el argumento como el path
		cmd[*i]->path = ft_strdup(cmd[*i]->args[0]);
	else										// si no se busca en env PATH
		locate_path(shell, cmd, i);
}