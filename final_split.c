/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:56:18 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/17 15:46:04 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Description:
		The funcion final_split create a double char pointer splitting
		the input string as the BASH shell would have done before analyzing
		the commands.
	Return value:
		The function returns the double char pointer with every string processed
		before analyzing commands.
*/

char	**final_split(char *input, char **envp)
{
	char	**final;
	//t_list	*cmds;
	final = split_quotes(input);
	final = ft_gest_ambiental(final, envp);
	print_arrarr(final);
	final = split_cmd(final);
	printf("\033[32m");
	print_arrarr(final);
	printf("Split len %d\n", ft_splitlen(final));
	final = trim_quotes(final);
	
	return (final);
}
