/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:08:44 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/07 19:44:08 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*s;
	int		fd;
	char	**split;

	(void)ac;
	(void)av;
	fd = open("./test", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("Numero stringhe of:%s>%d\n", s, count_strings(s));
		split = split_quotes(s);
		printf("\033[0;34mSimple Split\033[0m\n");
		print_arrarr(split);
		split = trim_quotes(split);
		printf("\033[0;32mTrimmed split\033[0m\n");
		print_arrarr(split);
		printf("End split\n");
		free(s);
		s = get_next_line(fd);
	}
	/* if (ac == 2)
		printf("%s", getenv(av[1])); */
}
