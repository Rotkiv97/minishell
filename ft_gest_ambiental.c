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
	char *ex;
	char *tmp;
	char *tmp2;
	int x;
	
	x = 0;
	while (envp[x] != '=' && envp[x])
		x++;
	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, av, i + 1);
	ex = ft_strdup(&envp[x + 1]);
	tmp2 = ft_strjoin(tmp, ex);
	free(tmp);
	free(ex);
	tmp = ft_strdup(&av[k]);
	ex = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	free(av);
	return(ex);
}

char *ft_rm_exp(char *av, int i, int k)
{
	char *tmp;
	char *tmp2;
	char *join;
	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, av, i + 1);
	tmp2 = ft_strdup(&av[k]);
	join = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return(join);
}

char *ft_expander(char *av, char **envp)
{
	char *separator;
	int i = 0;
	int k = 0;
	int x = 0;
	int flag;

	separator = "<>\\/|+-.,;:~{}[]()&%%\"^'#@?*$ ";
	while(av[i])
	{
			if(av[i] == '$')
			{
				k = i + 1;
				flag = 0;
				while(!ft_strchr(separator, av[k]) && av[k] != '\0')
					k++;
				while(envp[x])
				{
					if(!ft_strncmp(&av[i + 1], envp[x] , k - i - 1) && (k - i - 1) > 0)
					{
						av = ft_sub_dollar(av, envp[x], i, k);
						flag = 1;
					}
					x++;
				}
				if(flag == 0)
				{
					av = ft_rm_exp(av, i ,k);
					i--;
				}
				x = 0;
			}
/* 			else if (av[i] == '$' && av[i + 1] == '?')
				av = ft_sub_dollar(av, "=125", i, k); */
		i++;
	}
	return(av);
}
char **ft_gest_ambiental(char **av, char **envp)
{
	int x;


	x = 0;
	if(av == NULL)
		return(NULL);
	while(av[x])
	{
		if(av[x][0] == '\"' || av[x][0] != '\'')
		{
			av[x] = ft_expander(av[x], envp);	
		}

		x++;
	}
	return(av);
}
