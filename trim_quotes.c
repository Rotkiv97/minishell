/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:04:53 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/18 19:28:15 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_index_trim(char *s, int i)
{
	char	q;
	char	*set;

	set = "\'\"";
	while (s[i])
	{
		if (in_set((s[i]), set))
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			return (i);
		}
		else
			break ;
	}
	return (i);
}

char	*delete_quotes(char *s)
{
	int		j;
	int		k;
	char	*tmp;
	char	*join;

	j = 0;
	k = 0;
	join = 0;
	while (s[j])
	{
		if (in_set(s[j], "\"\'"))
		{
			k = ft_next_index_trim(s, j);
			tmp = malloc(sizeof(char) * (k - j));
			ft_strlcpy(tmp, &s[j + 1], k - j);
			join = ft_strjoin_free(join, tmp);
			j = k + 1;
		}
		else
		{
			k = j;
			while (s[k] && !in_set(s[k], "\"\'"))
				k++;
			tmp = malloc(sizeof(char) * (k - j + 1));
			ft_strlcpy(tmp, &s[j], k - j + 1);
			join = ft_strjoin_free(join, tmp);
			j = k;
		}
	}
	return (join);
}
/*
	Description:
		The function trim_quotes modify every string of 
		double char pointer exp trimming the quotes at the start
		and at the end of the string.
	Return value:
		It returns the same address of exp but the strings are modified.
*/

char	**trim_quotes(char **cmd)
{
	int	i;

	i = -1;
	if (!cmd)
		return (0);
	while (cmd[++i])
		cmd[i] = delete_quotes(cmd[i]);
	return (cmd);
}
