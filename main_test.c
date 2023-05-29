/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:08:44 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/29 17:09:38 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_status;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**fin;
	t_sh	shell;

	(void)ac;
	(void)av;
	shell.stdin_fd = dup(STDIN_FILENO);
	shell.stdout_fd = dup(STDOUT_FILENO);
	shell.envp = envp;
	ft_gest_sig_bash(0);
	printf("%d\n", getpid());
	while (1)
	{
		input = readline("\033[34mminishell>\033[0m");
		if (!input)
			break ;
		else if (ft_strlen(input))
		{
			fin = final_split(input, envp);
			shell.cmds = *ft_create_cmds(fin);
			ft_exe(&shell, shell.cmds);
			free_arrarr(fin);
			add_history(input);
		}
	}
}
