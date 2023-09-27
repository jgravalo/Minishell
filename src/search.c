/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:41:17 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 11:41:18 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
	char	*ptr;

	i = 0;
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/' || !docs)
		return (cmd);
	while (docs[i])
	{	
		ptr = docs[i];
		tmp = ft_strjoin(docs[i], "/");
		docs[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		free(ptr);
		if ((access(docs[i], F_OK)) != -1)
			return (docs[i]);
		i++;
	}
	return (NULL);
}

static void	locate_path(t_shell *shell, t_cmd **cmd, int i)
{
	int		env;
	char	**docs;

	env = get_path_env(shell->envp);
	if (env != -1)
	{
		docs = split_paths(shell->envp[env]);
		shell->tmp = get_path(docs, cmd[i]->args[0]);
		if (!shell->tmp || ft_strlen(cmd[i]->args[0]) == 0)
			cmd_not_found(cmd[i]->args[0]);
		cmd[i]->path = ft_strdup(shell->tmp);
		free(shell->tmp);
	}
	else
		filedir_not_found(cmd[i]->args[0]);
}

void	search(t_shell *shell, t_cmd **cmd, int i)
{
	struct stat	buf;

	if (ft_strchr(cmd[i]->args[0], '/'))
	{
		cmd[i]->path = ft_strdup(cmd[i]->args[0]);
		if (access(cmd[i]->path, F_OK) == -1)
			exit(cmd_error(cmd[i]->path, errno, 127));
		if (stat(cmd[i]->path, &buf) == -1)
			exit(cmd_error(cmd[i]->path, errno, 127));
		if (access(cmd[i]->path, X_OK) == 0 && S_ISDIR(buf.st_mode))
			exit(is_dir_error(cmd[i]->path, 126));
	}
	else
		locate_path(shell, cmd, i);
}
