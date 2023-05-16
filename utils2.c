/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:01:11 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/14 21:11:07 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_splitlen(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char	**ft_subsplit(char **split, int x, int y)
{
	char	**sub;
	int		len;
	int j;

	j = 0;
	if (!split)
		return (0);
	len = ft_splitlen(split);
	if (!len)
		return (0);
	if (x > len || y > len )
		return (0);
	sub = (char **) malloc (sizeof(char *) * (x - y + 1));
	while(y <= x && split[y])
	{
		sub[j] = ft_strdup(split[y]);
		j++;
		y++;
	}
	sub[j] = 0;
	return (sub);
}
