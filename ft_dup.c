#include "minishell.h"

int	main()
{
	int			fd;
	int			new_fd;
	int			dup;
	char		*s;
	struct stat	buf;

	fd = open("./to_do", O_RDONLY);
	printf("stat is :%d\n", stat("./to_dso", &buf));
	new_fd = 78;
	dup = dup2(fd, new_fd);
	printf("dup is : %d\n", dup);
	while (s = get_next_line(new_fd))
	{
		printf("%s", s);
	}
	return (0);
}