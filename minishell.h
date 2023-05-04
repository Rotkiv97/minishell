/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:39:55 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/04 18:56:26 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line_bonus.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct mshell
{
	char	**env;
}				t_mshell;

/*spit_quotes.c*/

char	**split_quotes(char *s);
int		count_strings(char *s);

/*utils1.c*/

char	**copy_arrarr(char **arr);
void	print_arrarr(char **arr);

/*utils1_free.c*/

void	free_arrarr(char **mat);

#endif