/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:08:44 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/21 16:55:24 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**fin;

	(void)ac;
	(void)av;
	printf("%d\n", getpid());
	while (1)
	{
		input = readline("\033[34mminishell>\033[0m");
		fin = final_split(input, envp);
		ft_create_cmds(fin);
		free_arrarr(fin);
		add_history(input);
	}
}
