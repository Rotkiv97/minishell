/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:52 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/04 19:06:49 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
	Finds next index; 
	the string s on cell ind is not a quote at the start of the function.
*/

/*
	Nelle parentesi chiuse posso non devo interpretare nulla.
	Mi fermo quando, dopo aver trovato un numero pari di parentesi, trovo un carattere tra >, >>, <, <<, | oppure spazio??. (un trattino - ?)
	Finche' non trovo uno di questi devo considerare la stringa ancora non terminata.

	CORREZIONE : 
	Considero una stringa ogni volta che si chiude una parentesi
*/

int	count_strings(char *s)
{
	int		strings;
	int		i;

	if (!s)
		return (0);
	i = 0;
	strings = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i = next_quote(s, i);
			if (i == -1)
				return (-1);
			strings++;
		}
		else if (s[i] != ' ')
		{
			i = jump_string(s , i);
		}
		while (s[i] == ' ')
			i++;
		
	}
	return (strings);
}

char	**split_quotes(char *s)
{
	char	**split;
	int		strings;

	split = 0;
	/* if (check_quotes(s))
		return (0); */
	strings = count_strings(s);
	(void)strings;
	//split = malloc(sizeof(char **) * (strings + 1));
	/* split = return_split();
	if (error_split(split))
	{
		free_arrarr(split);
		split = 0;
	} */
	return (split);
}
