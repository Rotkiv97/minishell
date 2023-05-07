/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:16:15 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/07 19:09:15 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_arrarr(char **arr)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	if (i == 0)
		return (0);
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

int	in_set(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	print_arrarr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
	{
		printf("No arrarr\n");
		return ;
	}
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
