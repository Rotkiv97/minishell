/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:04:05 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/12 19:05:11 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!arr[i])
			printf("Line %d is null\n", i);
		else
			printf("%s\n", arr[i]);
		i++;
	}
}
