/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2023/07/21 21:11:57 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_path(char **envp)
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

char	**split_docs(char *path)
{
	char	**docs;
	char	*dirs;

	dirs = ft_substr(path, 5, ft_strlen(path) - 5);
	docs = ft_split(dirs, ':');
	free(dirs);
	return (docs);
}

static char	*access_loop(char **docs, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (docs[i])
	{
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, cmd);
		if ((access(docs[i], F_OK)) != -1)
			return (docs[i]);
		i++;
	}
	//printf("%s: Command not found\n", cmd);
	free(tmp);
	return (NULL);
}

char	*access_cmd(char *cmd, char**docs, int env)
{
	if (cmd[0] != '/') 
		return (access_loop(docs, cmd));
	if (env == -1 && access(cmd, F_OK) == 0)
		return (cmd);
	if (is_local(cmd) == 0 && !(cmd[0] == '.' && cmd[1] == '/'))
	{
		cmd_error(cmd);
		exit(127);
	}
	if (access(cmd, F_OK) != -1 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd_error(cmd);
	exit(126);
}

char	*file_cmd(char *cmd, char **envp)
{
	int		env;
	char	*file;
	char	**docs;

	env = 0;
	if (!(cmd[0] == '.' && cmd[1] == '/'))
		env = search_path(envp);
	if (env != -1)
		docs = split_docs(envp[env]);
	else
		docs = split_docs(DEF_PATH);
	file = access_cmd(cmd, docs, env);
	free(docs);
	return (file);
}
