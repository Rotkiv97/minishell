/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:56:18 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/09 20:05:00 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**final_split(char *input)
{
	char	**final;

	final = split_quotes(input);
	printf("quotes_split:\n");
	print_arrarr(final);
	final = split_cmd(final);
	printf("cmd_split:\n");
	print_arrarr(final);
	final = trim_quotes(final);
	printf("trim_split:\n");
	print_arrarr(final);
	return (final);
}