/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:09:57 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/04 10:00:15 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/stat.h>

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

int isfile(const char* name)
{
	DIR* directory = opendir(name);

    if (directory != NULL)
		closedir(directory);
	return (errno);
}



static int	check_file_dir(t_shell *shell, char *file)
{	
	if (file[0] != '.')
	{
		if (isfile(file) != 0)
			return (cmd_error(file, errno, 127));
		else if (shell->args[1] == NULL) //solo hay un directorio y no hay comando, operacion ilegal "Is a directory"
			return (cmd_error(file, 21, 126));
	}
	if (access(file, F_OK) != 0)
		return (cmd_error(file, errno, 126));
	if (access(file, R_OK) != 0 || access(file, W_OK) != 0
		|| access(file, X_OK) != 0)
		return (cmd_error(file, errno, 126));
	return (0);
}

char	*file_cmd(t_shell *shell, int n)
{
	int		env;
	int		exit;
	char	*file;
	char	**docs;
	struct	stat buf;

	if (!shell->struct_cmd[n]->args)
		return ("empty");
/* 	if (check_builtin(shell->args) == 1)
		 */
	env = 0;
	env = search_path(shell->envp);
	if (env != -1)
	{
		docs = split_docs(shell->envp[env]); // split todos los paths
		file = access_loop(docs, shell->struct_cmd[n]->args[0]);
	}
	else // si no hay variable PATH, o se introduce el path completo del binario, o bash no lo encuentra
		file = access_loop(NULL, shell->struct_cmd[n]->args[0]);
	if (access(file, F_OK) != -1) // existe, pero no eje
	{	
		if (stat(file, &buf) == -1)
		{
			shell->exit = cmd_error(file, errno, 1);
			return (NULL);
		}
		if (S_ISDIR(buf.st_mode))
		{
			shell->exit = cmd_error(file, 21, 126);
			return (NULL);
		}
		return (file);
	}
	else if (file == NULL) // no ha encontrado comando, fuera
	{
		shell->exit = cmd_not_found(shell->struct_cmd[n]->args[0]);
		return (NULL);
	}
	else if (ft_strcmp(shell->struct_cmd[n]->args[0], file) == 0) //es file/dir
	{	
		//printf("entra en file/dir\n");
		shell->exit = check_file_dir(shell, file);
		if (shell->exit != 0) // si ha dado error fuera
			return (NULL);
		else				// si no, es un ejecutable, y sigue su camino hasta execve
			return (file);
	}
	else 
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
