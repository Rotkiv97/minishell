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
	

	//printf("%s", *anvp);
	//ft_gest_ambiental(anvp);
 	while(1)
	{
		input = readline("\033[32mminishell>$  \033[37m");
		str = split_quotes(input);
		str = ft_gest_ambiental(split_quotes(input), anvp);
		print_arrarr(split_quotes(input));
		//print_arrarr(anvp);
		add_history(input);
	}
	str =str;
}
