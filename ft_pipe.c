#include "minishell.h"

/*
	Quando apro una pipe ho 4 fd : 2 per il child e 2 per il parent, e tutti sono aperti;
	Non possiamo avere un pipe che manda e riceve sullo stesso processo.
	Bisogna ceare 2 pipes.
*/

/* void	ft_pipe(t_sh *shell, t_list *cmd, char *exe)
{
	int		cp[2];
	int		pc[2];
	int		pid;
	t_node	*tmp;

	if (pipe(cp) == -1)
		exit(-1);
	if (pipe(pc) == -1)
		exit(-1);
	while (cmd)
	{
		pid = fork();	
		if (pid == 0)
		{
			close(cp[0]); // chiudo lettura cp
			close(pc[1]); // chiudo scrittura pc
			tmp = (t_node *)cmd->content;
			if (tmp->infile == 0 && cmd != shell->cmds)
				dup2(pc[0], STDIN_FILENO);
			if (tmp->outfile == 1 && cmd->next)
				dup2(cp[1], STDOUT_FILENO);
			execve(exe, tmp->full_cmd, shell->envp);
		}
		else if (pid > 0)
		{
			char	*s;
			close(cp[1]);
			close(pc[0]);
			waitpid(pid, 0, 0);
			while (s = get_next_line(cp[0]))
				printf("%s", s);
		}
		cmd = cmd->next;
	}

}

int	main()
{
	int	fd[2];
	//fd[0] - read end
	//fd[1] - write end
	if (pipe(fd) == - 1)
		return (-1);
	int	id = fork(); // fd viene copiato nel figlio; i nuovi fd sono indipendenti dagli altri
	if (id == -1)
		return (4);
	if (id == 0)
	{
		int	x;
		close(fd[0]);
		printf("Input number:");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
			return (2);
		close(fd[1]);	//il file e' stato chiuso
	}
	else
	{
		int	y;
		close(fd[1]);
		if (read(fd[0], &y, sizeof(int)) == -1)
			return (3);
		close(fd[0]);
		printf("Got from child %d\n", y);
	}
	return (0);
} */

int	ft_read(int fd)
{
	char	c;

	while (read(fd, &c, 1))
	{
		printf("%c", c);
	}
}

int	main()
{
	int	fd[2];
	char *s;
	int		pid;


	pipe(fd);
	printf("fd[0] : %d, fd[1] : %d\n", fd[0], fd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		ft_putstr_fd("Come vaaaaa???????????", fd[1]);
		ft_putstr_fd("AKAKAK\n", fd[1]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		ft_read(fd[0]);
		close(fd[0]);
		waitpid(pid, 0, 0);
	}
	return (0);
}