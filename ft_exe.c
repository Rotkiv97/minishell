/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:57:26 by dcolucci          #+#    #+#             */
/*   Updated: 2023/06/01 16:09:53 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

char	*ft_cmd_finder(t_node *node, t_sh *shell)
{
	char	*cmd;
	char	**env_PATH;
	char	*full_cmd;
	int		x;

	(void)shell;
	x = 0;
	if (!(node->cmds))
		return (0);
	if (ft_strchr(node->cmds, '/'))
	{
		if (!access(node->cmds, F_OK | X_OK))
			return (node->cmds);
		else
		{
			printf("%s : no such file or directory\n", node->cmds);
			return (0);
		}
	}
	cmd = ft_strjoin("/", node->cmds);
	env_PATH = ft_split(getenv("PATH"), ':');
	while (env_PATH[x])
	{
		full_cmd = ft_strjoin(env_PATH[x], cmd);
		if (!access(full_cmd, F_OK | X_OK))
			return (full_cmd);
		free(full_cmd);
		x++;
	}
	if (!env_PATH[x])
	{
		printf("\033[3;31m%s : command not found🐓🐔\n\033[0m", node->cmds);
		g_status = 127;
	}
	return (0);
}

void	ft_prepare_redirection(t_sh *shell, t_list *cmd, int **fd, int i)
{
	t_node	*node;
	
	node = (t_node *)cmd->content;
	if (cmd == *(shell->cmds) && !cmd->next)	//one command
	{
		//printf("ONE\n");
		dup2(node->infile, STDIN_FILENO);
		dup2(node->outfile, STDOUT_FILENO);
	}
	else if (cmd == *(shell->cmds))			//first command
	{
		//printf("FIRST\n");
		if (ft_out(node))
			dup2(node->outfile, STDOUT_FILENO);
		else
			dup2(fd[i][1], STDOUT_FILENO);
		dup2(node->infile, STDIN_FILENO);
	}
	else if (!cmd->next)					//last command
	{
		//printf("LAST\n");
		if (ft_in(node))
			dup2(node->infile, STDIN_FILENO);
		else
			dup2(fd[i - 1][0], node->infile);
		dup2(shell->stdout_fd, STDOUT_FILENO);
		dup2(node->outfile, STDOUT_FILENO);
		//dup2(node->outfile, STDOUT_FILENO);
		
	}
	else									// middle command
	{
		//printf("MIDDLE\n");
		if (ft_out(node))
			dup2(node->outfile, STDOUT_FILENO);
		else
			dup2(fd[i][1], node->outfile);
		if (ft_in(node))
			dup2(node->infile, STDIN_FILENO);
		else
			dup2(fd[i - 1][0], node->infile);
	}
}

void	ft_reset_redirection(t_sh *shell)
{
	dup2(shell->stdin_fd, STDIN_FILENO);
	dup2(shell->stdout_fd, STDOUT_FILENO);
}

void	ft_exe(t_sh *shell, t_list *cmd)
{
	pid_t	pid;
	t_node	*node;
	int		**fd;
	int		i;
	char	*full_cmd;
	int		status;

	i = 0;
	if (!cmd)
		return ;
	if (ft_lstsize(cmd) > 1)
	{
		fd = (int **) malloc (sizeof(int) * (ft_lstsize(cmd) - 1));
		while (i < ft_lstsize(cmd) - 1)
		{
			fd[i] = (int *) malloc (sizeof(int) * 2);
			pipe(fd[i]);
			i++;
		}
	}
	i = 0;
	while (cmd)
	{
		node = (t_node *)cmd->content;
		ft_prepare_redirection(shell, cmd, fd, i);
		if (node->infile == -1 || node->outfile == -1)
		{
			if (node->infile == -1)
			{
				ft_putstr_fd("minishell : cannot open file ", shell->stdin_fd);
				ft_putstr_fd(node->str_infile, shell->stdout_fd);
				ft_putstr_fd("\n", shell->stdout_fd);
			}
			else if (node->outfile == -1)
			{
				ft_putstr_fd("minishell : cannot open file ", shell->stdout_fd);
				ft_putstr_fd(node->str_outfile, shell->stdout_fd);
				ft_putstr_fd("\n", shell->stdout_fd);
			}
		}
		else
		{
			if (!ft_builtins(node, shell))
			{
				full_cmd = ft_cmd_finder(node, shell);
				if (!full_cmd)
					break ;
				pid = fork();
				if (pid == 0)
				{
					execve(full_cmd, node->full_cmd, shell->envp);
					exit(0);
				}
				else
				{
					signal(SIGINT, SIG_IGN);
					signal(SIGQUIT, SIG_IGN);
					if (cmd->next)
						close(fd[i][1]);
					waitpid(pid, &status, 0);
					if (WIFEXITED(status))
						g_status = WEXITSTATUS(status);
					ft_gest_sig_bash();
				}
			}
		}
		cmd = cmd->next;
		i++;
	}
	ft_reset_redirection(shell);
}