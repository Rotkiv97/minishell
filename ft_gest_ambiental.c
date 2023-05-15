/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_ambiental.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:13:45 by vguidoni          #+#    #+#             */
/*   Updated: 2023/05/12 20:04:50 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sub_dollar(char *av, char *envp, int i, int k)
{
	char	*ex;
	char	*tmp;
	char	*tmp2;
	int		x;

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
	return (ex);
}

char	*ft_rm_exp(char *av, int i, int k)
{
	char	*tmp;
	char	*tmp2;
	char	*join;

	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, av, i + 1);
	tmp2 = ft_strdup(&av[k]);
	join = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	return (join);
}

char	*ft_av(char **envp, char *av, int i, int *flag)
{
	int		k;
	int		x;
	char	*separator;

	separator = "<>\\/|+-.,;:~{}[]()&%%\"^'#@?*$ ";
	x = 0;
	k = i + 1;
	while (!ft_strchr(separator, av[k]) && av[k] != '\0')
		k++;
	while (envp[x])
	{
		if (!compare_env(envp[x], &av[i + 1], k, i))
		{
			av = ft_sub_dollar(av, envp[x], i, k);
			*flag = 1;
		}
		x++;
	}
	if (*flag == 0)
		av = ft_rm_exp(av, i, k);
	return (av);
}

char	*ft_expander(char *av, char **envp)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (av[i])
	{
		if (av[i] == '$')
		{
			av = ft_av(envp, av, i, &flag);
			if (flag == 0)
				i--;
		}
		i++;
	}
	return (av);
}

/*
	Description:
		The function ft_gest_ambiental expand every $ variable in every string
		of av starting with double quotes (") or not starting with single quotes
		(');
	Return value:
		It returns a double char pointer with the $variable replaced 
		by its corresponding environment variable.
		If no variable is found the $xxx character (not in separators set) 
		are removed from the string.
*/

char	**ft_gest_ambiental(char **av, char **envp)
{
	int	x;

	x = 0;
	if (av == NULL)
		return (NULL);
	while (av[x])
	{
		if (av[x][0] == '\"' || av[x][0] != '\'')
		{
			av[x] = ft_expander(av[x], envp);
		}
		x++;
	}
	return (av);
}
