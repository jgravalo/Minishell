#include "../inc/minishell.h"

void set_redir(t_shell *shell, int n)
{	
	int i;

	i = 0;
	while (shell->struct_cmd[n]->redir[i])
	{
		if (INFILE)
		{	
			shell->struct_cmd[n]->infile = open(shell->struct_cmd[n]->redir[i]->path, O_RDONLY);
			if (shell->struct_cmd[n]->infile == -1)
			{
				shell->exit = 1;
				cmd_error(shell->struct_cmd[n]->redir[i]->path, errno, 1);
				break ;
			}
		}
		else if (HEREDOC)
			shell->struct_cmd[n]->infile = shell->struct_cmd[n]->redir[i]->heredoc_fd;
		else if (OUTFILE)
		{	
			shell->struct_cmd[n]->outfile = open(shell->struct_cmd[n]->redir[i]->path, O_RDWR | O_CREAT | O_TRUNC, 00644);
			if (shell->struct_cmd[n]->infile == -1)
			{
				shell->exit = 1;
				cmd_error(shell->struct_cmd[n]->redir[i]->path, errno, 1);
				break ;
			}
		}
		else if (OUTFILE_APPEND)
		{	
			shell->struct_cmd[n]->outfile = open(shell->struct_cmd[n]->redir[i]->path, O_RDWR | O_CREAT | O_APPEND, 00644);
			if (shell->struct_cmd[n]->infile == -1)
			{
				shell->exit = 1;
				cmd_error(shell->struct_cmd[n]->redir[i]->path, errno, 1);
				break ;
			}
		}
		
		i++;
	}
}