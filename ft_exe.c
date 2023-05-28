/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:57:26 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/28 19:52:30 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\033[3;31m%s : command not found🐓🐔\n\033[0m", node->cmds);
	return (0);
}

void	ft_exe2(t_sh *shell, t_list *cmd)
{
	int		fd[2];
	int		pid;
	t_node	*tmp;
	char	*full_cmd;
	int status;

	while (cmd->next)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			tmp = (t_node *) cmd->content;
			full_cmd = ft_cmd_finder(tmp, shell);
			if (!full_cmd)
				exit(-1);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(full_cmd, tmp->full_cmd, shell->envp);
		}
		else
		{
			close (fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			waitpid(pid, &status, 0);
			cmd = cmd->next;
		}
	}
	pid = fork();
	if (pid == 0)
	{
		tmp = (t_node *) cmd->content;
		full_cmd = ft_cmd_finder(tmp, shell);
		if (!full_cmd)
			exit(-1);
		execve(full_cmd, tmp->full_cmd, shell->envp);
	}
	else
		waitpid(pid, &status, 0);
	dup2(shell->stdin_fd, STDIN_FILENO);
}

void	ft_prepare_redirection(t_sh *shell, t_list *cmd, int **fd, int i)
{
	t_node	*node;
	
	node = (t_node *)cmd->content;
	if (cmd == shell->cmds && !cmd->next)	//one command
	{
		//printf("ONE\n");
		dup2(node->infile, STDIN_FILENO);
		dup2(node->outfile, STDOUT_FILENO);
	}
	else if (cmd == shell->cmds)			//first command
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

void	ft_reset_redirection(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

void	ft_exe(t_sh *shell, t_list *cmd)
{
	pid_t	pid;
	int		**fd;
	int		i;
	char	*full_cmd;

	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	i = 0;
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
		ft_prepare_redirection(shell, cmd, fd, i);
		/* else
			dup2(fd_out, STDOUT_FILENO); */
		if (!ft_builtins((t_node *)cmd->content, shell))
		{
			full_cmd = ft_cmd_finder((t_node *)cmd->content, shell);
			if (!full_cmd)
				return ;
			pid = fork();
			if (pid == 0)
				execve(full_cmd, ((t_node *)(cmd->content))->full_cmd, shell->envp);
			else
			{
				if(cmd->next)
				{
					close(fd[i][1]);
				} 
				waitpid(pid, 0, 0);
			}
		}
		else if (cmd->next)
			close(fd[i][1]);

		cmd = cmd->next;
		i++;
	}
	ft_reset_redirection(shell->stdin_fd, shell->stdout_fd);
}