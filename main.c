/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:20 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 16:33:24 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char		*input;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{	
		input = readline("\033[32mminishell>");
		add_history(input);
	}
	return (0);
}
