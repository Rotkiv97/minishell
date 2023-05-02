/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:38:52 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 19:08:17 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_even(char *trim, char quote)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (trim[i])
	{
		if (trim[i] == quote)
			count++;
	}
	if (count % 2)
		return (1);
	return (0);
}

int	check_quotes(char *s, t_mshell *msh)
{
	int		i;
	int		error;
	char	*trim;

	i = 0;
	error = 0;
	trim = ft_strtrim(s, "\"\'");
	if (trim[0] != trim[ft_strlen(trim) - 1])
		error = 1;
	if (trim[0] == '\"' && !check_even(trim, '\"'))
		error = 1;
	else if (trim[0] == '\'' && !check_even(trim, '\''))
		error = 1;
	free(trim);
	return (error);
}

char	**split_quotes(char *s, t_mshell *msh)
{
	char	**split;

	if (check_quotes(s, msh))
		return (0);
	split = malloc(sizeof(char **) * 2);
	split[0] = ft_strtrim(s, "\'\"");
	split[1] = 0;
	return (split);
}
