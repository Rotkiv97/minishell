#include "minishell.h"

int	ft_heredoc(char *delimiter)
{
	char *inp_heredoc;
	int fd;

	fd = open("tmp", O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
	while(1)
	{
		inp_heredoc = readline("\033[33m🤟🍀🤟>\033[0m");
		if(!ft_strncmp(inp_heredoc, delimiter,ft_max(ft_strlen(inp_heredoc), ft_strlen(delimiter))))
			break;
		ft_putstr_fd(inp_heredoc,fd);
		ft_putstr_fd("\n", fd);
		
	}
	return(fd);
}