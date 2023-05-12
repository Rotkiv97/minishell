/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:12:34 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/11 17:44:28 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_sep(char *s, char *set)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 1;
	while (s[i])
	{
		if (in_set(s[i], set))
		{
			flag = 1;
			count++;
		}
		else if (flag == 1)
		{
			count++;
			flag = 0;
		}
		i++;
	}
	return (count);
}

void	fill_nano(char **nano, char *exp, char *set)
{
	int	i;
	int	j;
	int	k;
	int	sep;

	i = 0;
	j = 0;
	k = 0;
	sep = count_sep(exp, set);
	while (exp[i] && k < sep)
	{
		if (in_set(exp[i], set))
		{
			nano[k] = (char *) malloc (sizeof (char) * 2);
			nano[k][0] = exp[i];
			nano[k][1] = '\0';
			k++;
			i++;
		}
		else
		{
			j = i;
			while (exp[j] && !in_set(exp[j], set))
				j++;
			nano[k] = malloc (sizeof(char) * (j - i + 1));
			ft_strlcpy(nano[k], &exp[i], (j - i + 1));
			k++;
			i = j;
		}
	}
	nano[k] = 0;
}

char	**nano_split_cmd(char *exp)
{
	int		sep;
	char	**nano;

	if (!find_next_char(exp, "<>|", 0) || in_set(exp[0], "\'\""))
	{
		nano = (char **) malloc (sizeof (char *) * (2));
		nano[0] = ft_strdup(exp);
		nano[1] = 0;
		return (nano);
	}
	sep = count_sep(exp, "<>|");
	nano = (char **) malloc (sizeof(char *) * (sep + 1));
	fill_nano(nano, exp, "<>|");
	return (nano);
}

char	**join_split(char **cmd, char **line_spl)
{
	char	**join;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!cmd)
		return (line_spl);
	while (cmd[i])
		i++;
	while (line_spl[j])
		j++;
	join = (char **) malloc (sizeof(char *) * (i + j + 1));
	while (cmd[k])
	{
		join[k] = ft_strdup(cmd[k]);
		k++;
	}
	i = 0;
	while (line_spl[i])
		join[k++] = ft_strdup(line_spl[i++]);
	join[k] = 0;
	free_arrarr(cmd);
	free_arrarr(line_spl);
	return (join);
}

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
