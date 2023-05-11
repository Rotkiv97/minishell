/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:39:55 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/09 20:01:03 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line_bonus.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct mshell
{
	char	**env;
}				t_mshell;

/*split_command.c*/

int		count_sep(char *s, char *set);
char	**nano_split_cmd(char *exp);
char	**split_cmd(char **exp);

/*spit_quotes.c*/

char	**split_quotes(char *s);

/*expand_vars.c*/

char	**expand_vars(char **mat);

/*trim_quotes.c*/

char	**trim_quotes(char **exp);

/*final_split.c*/

char	**final_split(char *input);

/*utils1.c*/

int		in_set(char c, char *s);
char	*find_next_char(char *str, char *set, int i);
char	**copy_arrarr(char **arr);
void	print_arrarr(char **arr);

/*utils1_free.c*/

void	free_arrarr(char **mat);



#endif