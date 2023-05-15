/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:20 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/12 20:05:04 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int ac, char **av, char **anvp)
{

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{	
		input = readline("\033[32mminishell>\033[0m");
		print_arrarr(split_quotes(input));
		add_history(input);
		free_arrarr(str);
		free(input);
	}
	str =str;
}
