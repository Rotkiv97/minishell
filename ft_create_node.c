/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:00:19 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/18 19:05:57 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*per vedere file descriptor aperti -> cd /proc/$$/fd*/

int ft_infile(char **sub_cmd)
{
	int fd_k;
	int x;
	int fd;

	x = 0;
	fd = 0;
	while(sub_cmd[x])
	{
		if(in_set(sub_cmd[x][0], "<"))
		{
			if(sub_cmd[x + 1][0] == '<')
			{
				if(fd != 0)
						close(fd);
				fd = ft_heredoc(sub_cmd[x + 2]);
				x = x + 2;
			}
			else
			{
				fd_k = open(sub_cmd[x + 1], O_RDONLY);
				if(fd_k == -1)
					ft_quit(ft_strjoin("\033[31mCannot open ", sub_cmd[x + 1]), -1);
				else
				{
					if(fd != 0)
						close(fd);
					fd = fd_k;
				}
				x = x + 1;
			}
		}
		else 
			x++;
	}
	return(fd);
}

/* O_WRONLY -> apre il file con permesso di scrittura 
|| O_APPEND -> aggiunge l'output al file senza sovrascrivere 
|| O_CREAT -> crea il file se non esiste
|| S_IRWXU -> da al file i permessi scrivere, leggere ed eseguire
|| O_TRUNC -> sovrascirive il file precedente
*/

int ft_outfile(char **sub_cmd)
{
	int fd;
	int x;
	int fd_k;

	x = 0;
	fd = 1;
	while(sub_cmd[x])
	{
		if(sub_cmd[x][0] == '>')
		{
			if(sub_cmd[x + 1][0] == '>')
			{
				fd_k = open(sub_cmd[x + 2], O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
				if (fd_k == -1)
					ft_quit(ft_strjoin("Cannot open file ", sub_cmd[x + 2]), -2);
				else
				{
					if(fd != 1)
						close(fd);
					fd = fd_k;
				}
				x = x + 2;
			}
			else
			{
				fd_k = open(sub_cmd[x + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
				if (fd_k == -1)
					ft_quit(ft_strjoin("Cannot open file ", sub_cmd[x + 1]), -2);
				else
				{
					if(fd != 1)
						close(fd);
					fd = fd_k;
				}
				x = x + 1;
			}
		}
		else 
			x++;
	}
	return(fd);
}

char *ft_cmd(char **sub_cmd)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = 0;
	while (sub_cmd[i])
	{
		if (!in_set(sub_cmd[i][0], "<>"))
		{
			cmd = (ft_strdup(sub_cmd[i]));
			return (cmd);
		}
		else
		{
			while (sub_cmd[i] && in_set(sub_cmd[i][0], "<>"))
				i++;
			if (!sub_cmd[i])
				break ;
			else
				i++;
		}
	}
	return (cmd);
}

char	**ft_full_cmd(char **sub_cmd)
{
	int		i;
	char	**full_cmd;

	i = 0;
	full_cmd = 0;
	while (sub_cmd[i])
	{
		if (!in_set(sub_cmd[i][0], "<>"))
		{
			full_cmd = ft_add_to_split(full_cmd, sub_cmd[i]);
			i++;
		}
		else
		{
			while (sub_cmd[i] && in_set(sub_cmd[i][0], "<>"))
				i++;
			if (!sub_cmd[i])
				break ;
			else
				i++;
		}
	}
	return (full_cmd);
}