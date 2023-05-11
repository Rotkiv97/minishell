/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:08:44 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/11 18:22:04 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
/* 	char	*s;
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
	} */
	/* if (ac == 2)
		printf("%s", getenv(av[1])); */

	
/* 	char	*input;
	char	**split;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("\033[32mminishell>\033[0m");
		printf("Numero stringhe of:%s>%d\n", input, count_strings(input));
		split = split_quotes(input);
		printf("\033[0;34mSimple Split\033[0m\n");
		print_arrarr(split);
		split = trim_quotes(split);
		printf("\033[0;32mTrimmed split\033[0m\n");
		print_arrarr(split);
		free(split);
	} */
	
	char	*input;
	char	**fin;

	(void)ac;
	(void)av;
	while (1)
	{
		input = readline("\033[34mminishell>\033[0m");
		fin = final_split(input, envp);
		print_arrarr(fin);
		free_arrarr(fin);
		add_history(input);
	}

}

/* "ciaoc comea va $PWD ciao $USER" */
