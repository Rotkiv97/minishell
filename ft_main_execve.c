/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:41:19 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/21 17:37:13 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve("./minishell_test", av, envp);
	}
	else if (pid)
	{
		waitpid(pid, 0, 0);
	}
	else if (pid < 0)
	{
		ft_quit("error", -1);
	}
	return (0);
}