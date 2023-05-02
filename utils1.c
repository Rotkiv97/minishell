/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:16:15 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 16:05:55 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_arrarr(char **arr)
{
	int		i;
	char	**cpy;

	i = 0;
	while (arr[i])
		i++;
	cpy = malloc(sizeof(char **) * (i + 1));
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

int	unclosed_quotes(char *s)
{
	(void)s;
	return (0);
}

char	**split_quotes(char *s)
{
	char	**split;

	if (unclosed_quotes(s))
		return (0);
	split = 0;
	return (split);
}

void	print_arrarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
