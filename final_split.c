/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:56:18 by dcolucci          #+#    #+#             */
/*   Updated: 2023/06/02 20:05:06 by dcolucci         ###   ########.fr       */
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
extern int g_status;

char	**final_split(char *input, char **envp)
{
	char	**final;

	final = split_quotes(input);
	final = ft_gest_ambiental(final, envp);
	g_status = 0;
	final = split_cmd(final);
	printf("CMD\n");
	print_arrarr(final);
	final = trim_quotes(final);
	printf("TRIM\n");
	print_arrarr(final);
	return (final);
}
