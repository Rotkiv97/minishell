/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:57:26 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/21 18:01:56 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_path_finder(t_node *node)
{
	char	*full_path;
	char	*cmd;
}

void	ft_executor()
{
	
}

void	ft_exe(t_list *cmds, t_sh *shell)
{
	t_list	*tmp;
	char	*cmd_path;

	node = cmds;
	if (!cmds!)
		return ;
	while (tmp)
	{
		cmd_path = ft_path_finder((t_node *)tmp->data);
		ft_executor(cmd_path, (t_node *)tmp->data);
		tmp = tmp->next;
	}
}
