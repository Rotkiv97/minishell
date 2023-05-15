/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:56:10 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/15 15:40:33 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_redirection(char **sub_cmd, char redir)
{
	int		x;
	int		count;

	x = 0;
	count = 0;
	while (sub_cmd[x])
	{
		if (sub_cmd[x][0] == redir && (int)ft_strlen(sub_cmd[x]) == 1)
			count++;
		else if (sub_cmd[x][0] != redir && in_set(sub_cmd[x][0], "<>") \
			&& (int)ft_strlen(sub_cmd[x]) == 1)
			return (INT_MAX);
		x++;
	}
	return (count);
}

void	ft_check_syntax(char **sub_cmd)
{
	int		x;
	int		count;
	char	*error;

	x = 0;
	count = 0;
	error = "\033[7m\033[33mSytax error using < >\n\033[0m";
	if (!sub_cmd)
		return ;
	while (sub_cmd[x])
	{
		if (in_set(sub_cmd[x][0], "<>"))
		{
			count = ft_count_redirection(&sub_cmd[x + 1], sub_cmd[x][0]);
			if (count > 2 || !sub_cmd[x + 1])
				ft_quit(error, -1);
		}
	}
}
