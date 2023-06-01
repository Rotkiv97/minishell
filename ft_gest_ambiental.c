/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_ambiental.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 10:13:45 by vguidoni          #+#    #+#             */
/*   Updated: 2023/06/01 20:46:17 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

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

	separator = "<>\\/|+-.,;:~{}[]()&%%\"^'#@*$? ";
	x = 0;
	k = i + 1;
	while (!ft_strchr(separator, av[k]) && av[k] != '\0')
		k++;
	if(av[1] == '?')
		return (ft_strjoin(ft_itoa(g_status), &av[2]));
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

int		ft_next_quote_exp(char *s, int i)
{
	char	q;

	if (in_set(s[i], "\'\""))
	{
		q = s[i];
		while (s[i] && s[i] != q)
			i++;
	}
	else
	{
		while (!in_set(s[i], "\'\""))
			i++;
	}
	return (i);
}

char	*ft_expand(char *to_exp)
{
	
}

char	*ft_expander(char *exp, char **envp)
{
	int		i;
	int		k;
	char	*join;
	char	*tmp;
	char	*to_exp;

	i = 0;
	k = 0;
	while (exp[i])
	{
		k = ft_next_quote_exp(exp, i);
		if (exp[i] != '\'')
		{
			to_exp = ft_substr(&exp[i], 0, k);
			tmp = ft_expand(to_exp);
			join = ft_strjoin(join, tmp);
		}
		else
		{
			tmp = (char *) malloc (sizoef(char) * (k + 1));
			ft_strlcpy(tmp, &exp[i], k + 1);
			join = ft_strjoin(join, tmp);
			i = k + 1;
		}
	}
	return (exp);
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
		av[x] = ft_expander(av[x], envp);
		x++;
	}
	return (av);
}
