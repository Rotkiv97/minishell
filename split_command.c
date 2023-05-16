/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:12:34 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/12 19:45:23 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_sep_cmd(char *s, char *set)
{
	int		i;
	int		count;
	int		flag;
	char	*set;
	char	q;

	i = 0;
	count = 0;
	flag = 1;
	while (s[i])
	{
		while (s[i] && !in_set(s[i], "\'\""))
		{
			if (in_set(s[i], "<>|"))
				count++;
		}
	}
	return (count);
}

void	fill_nano(char **nano, char *exp, char *set)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (exp[i] && k < count_sep_cmd(exp, set))
	{
		if (in_set(exp[i], set))
		{
			nano[k] = (char *) malloc (sizeof (char) * 2);
			ft_strlcpy(nano[k++], &exp[i++], 2);
		}
		else
		{
			j = i;
			while (exp[j] && !in_set(exp[j], set))
				j++;
			nano[k] = malloc (sizeof(char) * (j - i + 1));
			ft_strlcpy(nano[k++], &exp[i], (j - i + 1));
			i = j;
		}
	}
	nano[k] = 0;
}

char	**nano_split_cmd(char *exp)
{
	int		sep;
	int		y;
	char	**nano;

	y = 0;
	while(exp[y])
	{
		if (!find_next_char(exp, "<>|", 0) || in_set(exp[y], "\'\""))
		{
			
			nano = (char **) malloc (sizeof (char *) * (2));
			nano[0] = ft_strdup(exp);
			nano[1] = 0;
			
			return (nano);
		}
		y++;
	}
	sep = count_sep_cmd(exp, "<>|");
	nano = (char **) malloc (sizeof(char *) * (sep + 1));
	
	fill_nano(nano, exp, "<>|");
	printf("ciao-------------\n");
	return (nano);
}

char	**join_split(char **cmd, char **line_spl)
{
	char	**join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd)
		return (line_spl);
	while (cmd[i])
		i++;
	while (line_spl[j])
		j++;
	join = (char **) malloc (sizeof(char *) * (i + j + 1));
	i = 0;
	j = 0;
	while (cmd[i])
		join[j++] = ft_strdup(cmd[i++]);
	i = 0;
	while (line_spl[i])
		join[j++] = ft_strdup(line_spl[i++]);
	join[j] = 0;
	free_arrarr(cmd);
	free_arrarr(line_spl);
	return (join);
}

/*
	Description :
		split_cmd function split every string of the exp double 
		char pointer with the separators set equals to "<>|".
	Return Value :
		It returns a double char pointer where every char in separators set "<>|"
		are splitted in single strings.
*/

char	**split_cmd(char **exp)
{
	char	**split_cmd;
	char	**line_spl;
	int		x;

	x = 0;
	split_cmd = 0;
	if (exp == NULL)
		return (NULL);
	while (exp[x])
	{
		line_spl = nano_split_cmd(exp[x]);
		if (!line_spl)
			return (0);
		split_cmd = join_split(split_cmd, line_spl);
		x++;
	}
	free(exp);
	return (split_cmd);
}
