/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:20 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 19:16:18 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main (int ac, char **av, char **anvp)
{

	(void)ac;
	(void)av;
	(void)anvp;
	char *input;
	char **str;
	char **spl;
	

	//printf("%s", *anvp);
	//ft_gest_ambiental(anvp);
 	while(1)
	{
		input = readline("\033[32mminishell>$  \033[37m");
		spl = split_quotes(input);
		print_arrarr(split_quotes(input));
		str = ft_gest_ambiental(spl, anvp);
		printf("\033[33mcopy----------: \n");
		print_arrarr(str);
		//print_arrarr(anvp);
		add_history(input);
		free_arrarr(str);
		free(input);
	}
	str =str;
}
