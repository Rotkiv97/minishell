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

char *ft_sub_dollar(char *av, char *envp, int i , int k)
{
	int x;
	x = 0;
	while (envp[x])
	{
		printf("%s\n", envp);
		x++;
	}
	return(av);
}

char *ft_expander(char *av, char **envp)
{
	char *separator;
	int i = 0;
	int k = 0;
	int x = 0;

	separator = "<>\\/|+-.,;:~{}[]()&%%^#@'?* ";
	while(av[i])
	{
		if(av[i] == '$')
		{
			k =  i + 1;
			while(!ft_strchr(separator, av[k]) || av[k] != '\0')
				k++;
			while(envp[x])
			{
				int l = 0;
				if(!ft_strncmp(&av[i + 1], envp[x] , k - i - 1))
					av = ft_sub_dollar(av, envp[x], i, k);
				x++;
			}

		}
		i++;
	}
	return(av);
}

/* char **ft_get_getenv(char **av)
{
	const char *separator;
	int k;
	int y;
	int x;

	k = 0;
	y = 0;
	x = 0; 
	separator = '\0';
	separator = "<>\\/|+-.,;:~{}[]()&%%^#@'?*";
	if(av[x][y] == '$')
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
 */
char **ft_gest_ambiental(char **av, char **envp)
{
	int x;


	x = 0;
	while(av[x])
	{
		if(av[x][0] == '\"' || av[x][0] != '\'')
		{
			av[x] = ft_expander(av[x], envp);
			//ft_get_getenv(av);	
		}
		/* while(av[i])
		{
			printf("%s", av[i]);
			i++;
		} */
		x++;
	}
	return(av);
}
