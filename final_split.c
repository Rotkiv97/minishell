/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:56:18 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/11 18:22:24 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**final_split(char *input, char **envp)
{
	char	**final;

	final = split_quotes(input);
	final = ft_gest_ambiental(final, envp);
	final = split_cmd(final);
	final = trim_quotes(final);
	return (final);
}
