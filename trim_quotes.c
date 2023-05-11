/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:04:53 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/09 17:18:22 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quotes(char *to_trim, char quote)
{
	char	*trim;
	char	*tmp;
	char	q[2];

	tmp = to_trim;
	q[0] = quote;
	q[1] = '\0';
	trim = ft_strtrim(to_trim, q);
	free(tmp);
	return (trim);
}

char	**trim_quotes(char **exp)
{
	int		i;

	i = 0;
	if (!exp)
		return (0);
	while (exp[i])
	{
		if (in_set(exp[i][0], "\'\""))
			exp[i] = delete_quotes(exp[i], exp[i][0]);
		i++;
	}
	return (exp);
}
