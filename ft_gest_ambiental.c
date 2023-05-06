/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_ambiental.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vguidoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:13:45 by vguidoni          #+#    #+#             */
/*   Updated: 2023/05/06 10:13:54 by vguidoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
void ft_check_ambiental(char **av)
{
	int x;
	int y;

	x = 1;
	y = 0;
	if(av[x][y] == 92 && av[x][y + 1] == 36)
	{
		printf("$%s", *av);
	}
}


char **ft_get_getenv(char **av)
{
	const char *separator;
	int k;
	int y;
	int x;

	k = 0;
	y = 0;
	x = 1; 
	separator = '\0';
	separator = "<>\\/|+-.,;:~{}[]()&%%^#@'?*";
	//
/* 	if(av[x][y] == 36 && av[x][y - 1] == 92)
	{
		
	} */
	if(av[x][y] == 36 && av[x][y - 1] != 92)
	{
		k = y;
		while(av[x][k] != ' ' && av[x][k] != '\0')
			k++;
		char *str = malloc(sizeof(char) * ((k - y) + 1));
		ft_strlcpy(str, &av[x][y] ,k - y + 1);
		av[y] = ft_strchr(separator, av[x][k]);
		if(av[x][y] == separator[y])
			printf("%c", av[x][y]);			
	}
	
	return(av);
}

char **ft_gest_ambiental(char **av)
{
	int y;
	int x;

	y = 0;
	x = 1;
	int i = 1;
	while(av[x])
	{
		if(av[x][0] == 34 || av[x][0] != 39)
		{
			while(av[x][y] && av[x][y] != '$')
				y++;
			av = ft_get_getenv(av);
			y = 0;	
		}
		i = 1;
		while(av[i])
		{
			printf("%s", av[i]);
			i++;
		}
		x++;
	}
	return(av);
}
