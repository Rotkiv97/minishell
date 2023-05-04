/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:08:44 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/04 17:22:29 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*s;
	int		fd;

	fd = open("./test", O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		printf("Numero stringhe of |%s->%d\n", s, count_strings(s));
		free(s);
		s = get_next_line(fd);
	}
	free(s);
}
