/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/18 16:23:02 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


t_list	*ft_new_cmd(char **sub_spl)
{
	//t_node	*node;
	//t_list	*new;

	ft_check_syntax(sub_spl);
	//node = (t_node *) malloc (sizeof(t_node));
/* 	node->infile = ft_infile();
	node->outfile = ft_outfile();
	node->full_cmd = ft_full_cmd();
	node->cmds = ft_full_cmd();
	new = ft_lstnew(); */
	//printf("\033[35mCommand is : %s\n", ft_cmd(sub_spl));
	//printf("\033[31mFull_cmd is :\n");
	//print_arrarr(ft_full_cmd(sub_spl));
	printf("\033[35mintfile is : [%d] \n", ft_infile(sub_spl));
	return (0);
}

t_list	*ft_create_cmds(char **final)
{
	int		x;
	int		y;
	char	**sub_split;

	x = 0;
	y = 0;
	if (final == NULL)
		return (NULL);
	while (final[x])
	{
		if (final[x][0] == '|')
		{
			sub_split = ft_subsplit(final, y, x);
			ft_new_cmd(sub_split);
			y = x + 1;
		}
		x++;
	}
	sub_split = ft_subsplit(final, y, x);
	ft_new_cmd(sub_split);
	return (0);
}
