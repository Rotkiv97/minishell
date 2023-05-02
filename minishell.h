/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:39:55 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/02 19:06:44 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct mshell
{
	char	**env;
}				t_mshell;

char	**split_quotes(char *s, t_mshell *msh);

char	**copy_arrarr(char **arr);
void	print_arrarr(char **arr);

#endif