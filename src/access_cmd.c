/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2023/08/15 13:48:09 by theonewhokn      ###   ########.fr       */
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
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		return (cmd);
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
//	return (cmd);
}

int isfile(const char* name)
{
	DIR* directory = opendir(name);

    if (directory != NULL)
	{
		closedir(directory);
		return (0);
	}
    if (errno == ENOTDIR)
		return (1);
	return (-1);
}



int	check_cmd(char *cmd)
{
	if (isfile(cmd) == 0)
	{
		cmd_error(cmd, 21, 127);
		/*
		write(2, cmd, ft_strlen(cmd));
		write(2, ": is a directory\n", 16);
		exit(127);
		*/
	}
	if (cmd[0] == '.' && cmd[1] == '/')
		cmd += 2;
	if (access(cmd, F_OK) != 0)
	{
		cmd_error(cmd, 2, 127);
		exit(127);
		return (cmd_error(cmd, 13, 126));
//		exit(cmd_error(cmd, 13, 126));
	}
	if (access(cmd, R_OK) != 0 || access(cmd, W_OK) != 0
		|| access(cmd, X_OK) != 0)
	{
		return (cmd_error(cmd, 13, 126));
//		exit(cmd_error(cmd, 13, 126));
	}
	return (0);
}

char	*file_cmd(char *cmd, char **envp)
{
	int		env;
	int		exit;
	char	*file;
	char	**docs;

	env = 0;
	if (!(cmd[0] == '.' && cmd[1] == '/'))
		env = search_path(envp);
	if (env != -1)
		docs = split_docs(envp[env]);
	else
		docs = split_docs(DEF_PATH);
	file = access_loop(docs, cmd);
	exit = check_cmd(cmd);
//	file = access_cmd(cmd, docs, env);
	free(docs);
	return (file);
}

/*
char	*access_cmd(char *cmd, char**docs, int env)
{
	if (cmd[0] != '/') 
		return (access_loop(docs, cmd));
	if (env == -1 && access(cmd, F_OK) == 0)
		return (cmd);
	if (is_local(cmd) == 0 && !(cmd[0] == '.' && cmd[1] == '/'))
	{
		cmd_error(cmd, 2, 127);
		exit(126);
	}
	if (access(cmd, F_OK) != -1 && access(cmd, X_OK) != -1)
		return (cmd);
	cmd_error(cmd, 2, 127);
	exit(126);
}
*/
