/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:52 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/12 17:00:56 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It finds next index after the first quote. 
If there is no matching quote it returns -1; 
*/

int	next_quote(char *s, int i, char q)
{
	while (s[i] && s[i] != q)
		i++;
	if (!s[i])
		return (-1);
	return (i + 1);
}

/*Nelle parentesi chiuse posso non devo interpretare nulla.
Mi fermo quando, dopo aver trovato un numero pari di parentesi,
trovo un carattere tra >, >>, <, <<, | oppure spazio??. (un trattino - ?)
Finche' non trovo uno di questi devo considerare la stringa ancora non terminata.

CORREZIONE : 
Considero una stringa ogni volta che si chiude una parentesi
*/

int	count_strings(char *s)
{
	int		strings;
	int		i;

	i = 0;
	strings = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (in_set(s[i], "\'\""))
		{
			i = next_quote(s, i + 1, s[i]);
			if (i == -1)
				return (0);
			strings++;
		}
		else if (s[i])
		{
			while (s[i] && !in_set(s[i], " \'\""))
				i++;
			strings++;
		}
	}
	return (strings);
}

int	fill_line(char **line, char *s, int j)
{
	int	k;

	k = 0;
	if (in_set(s[j], "\"\'"))
	{
		k = next_quote(s, j + 1, s[j]);
		*line = (char *) malloc(sizeof(char) * (k - j + 1));
		ft_strlcpy(*line, &s[j], (k - j + 1));
	}
	else if (s[j])
	{
		k = j;
		while (s[k] && !in_set(s[k], " \'\""))
			k++;
		*line = (char *) malloc(sizeof(char) * (k - j + 1));
		ft_strlcpy(*line, &s[j], (k - j + 1));
	}
	return (k);
}

char	**fill_split(char **split, char *s, int strings)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < strings && s[j])
	{
		if (s[j] == ' ')
		{
			while (s[j] && s[j] == ' ')
				j++;
		}
		else if (in_set(s[j], "\"\'"))
			j = fill_line(&split[i++], s, j);
		else if (s[j])
			j = fill_line(&split[i++], s, j);
	}
	split[i] = 0;
	return (split);
}

char	**split_quotes(char *s)
{
	char	**split;
	int		strings;

	split = 0;
	strings = count_strings(s);
	if (strings == 0)
		return (0);
	split = (char **) malloc(sizeof(char *) * (strings + 1));
	split = fill_split(split, s, strings);
	return (split);
}
