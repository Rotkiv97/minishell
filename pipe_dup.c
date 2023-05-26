#include "minishell.h"

int	main()
{
	int		fd[2];
	int		pid;
	char	buf[100];

	pipe(fd);
	for(int i = 0; i < 2; i++){
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			sleep(2);
			if (i == 0)
				write(fd[1], "Ciaooooooo\0", 9);
			else
				write(fd[1], "Po\0", 2);
			//close(fd[1]);
			exit(0);
		}
		else if (pid > 0)
		{
			//close(fd[1]);
			read(fd[0], buf, 30);
			//close(fd[0]);
			printf("%s\n", buf);
			printf("%p is the add of buf\n", buf);
			waitpid(pid, 0, 0);
		}
	}
}