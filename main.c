/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:48:20 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 19:16:18 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//printf("%s\n", getenv(&str[1]));

					/*
						trovare i separatori[>,/, -, +, <, *, . , , , ~, =, \, |, ]
						cestire cetenv
						attenzio el dollaro$
					*/
					//printf("\n");
#include "minishell.h"
char **ft_get_getenv(char **av)
{
	const char *separatori;
	int k;
	int y;
	int x;

	k = 0;
	y = 0;
	x = 1; 
	separatori = '\0';
	separatori = "<>\\|/*+-.,;:~{}[]()&%%^#@'?";
	if(av[x][y] == 36)
	{
		k = y;
		while(av[x][k] != ' ' && av[x][k] != '\0')
			k++;
		char *str = malloc(sizeof(char) * ((k - y) + 1));
		ft_strlcpy(str, &av[x][y] ,k - y + 1);
		av[y] = ft_strchr(separatori, av[x][k]);
		if(av[x][y] == separatori[y])
			printf("%c", av[x][y]);					
					
	}
	return(av);
}

int	main(int ac, char **av)
{
	int y = 0;
	int x = 1;
	//const char *str;
	//char **str;
	//str = malloc(sizeof(char) * ft_strlen(*av));
	y = 0;
	if(ac == 2)
	{
		while(av[x])
		{
			
			if(av[x][0] == 34 || av[x][0] != 39)
			{
				while(av[x][y] && av[x][y] != '$')
				{
					printf("%c", av[x][y]);
					y++;
				}
				av = ft_get_getenv(av);
				y = 0;	
			}
			x++;
		}
	}	
	printf("\n");
	return (0);
}
/* 
	expander var file -> get env
 */
