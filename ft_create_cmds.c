/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:58:07 by vguidoni          #+#    #+#             */
/*   Updated: 2023/05/14 21:04:15 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_new_cmd(char **full_cmds, int x, int y)
{
	//t_node	*node;
	//t_list	*new;
	char	**sub_cmd;


	//node = (t_node *) malloc (sizeof(t_node));
	sub_cmd = ft_subsplit(full_cmds, x, y);
/* 	node->infile = ft_infile();
	node->outfile = ft_outfile();
	node->full_cmd = ft_full_cmd();
	node->cmds = ft_full_cmd();
	new = ft_lstnew(); */

	sub_cmd = sub_cmd;
	x = x;
	y = y;
	return (0);
}

t_list	*ft_create_cmds(char **full_cmds)
{
	//t_list	*cmds;
	//t_list	*new;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (full_cmds == NULL)
		return (NULL);
	while (full_cmds[x])
	{
		if (full_cmds[x][0] == '|')
		{
			ft_new_cmd(full_cmds, x, y);
			y = x;
		}
		x++;
	}
	ft_new_cmd(full_cmds, x, y);
	//new = new;
	return (0);
}
