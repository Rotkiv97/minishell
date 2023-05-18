/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:39:55 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/18 19:15:12 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "gnl/get_next_line_bonus.h"

# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

//int g_status;

typedef struct s_sh
{
	t_list	*cmds;
	char	**envp;
	pid_t	pid;
}t_sh;


typedef struct s_node
{
	char	**full_cmd;
	char	*cmds;
	int		infile;
	int		outfile;
}t_node;

/*ft_quit.c*/

void	ft_quit(char *error, int quit);

/*ft_check_syntax.c */

void	ft_check_syntax(char **sub_cmd);
int		ft_count_redirection(char **sub_cmd, char redir);

/*split_command.c*/

int		count_sep(char *s, char *set);
char	**nano_split_cmd(char *exp);
char	**split_cmd(char **exp);

/*spit_quotes.c*/

int		ft_next_index_quote(char *s, int i);
char	**split_quotes(char *s);

/*ft_create_cmds.c*/

t_list	**ft_create_cmds(char **full_cmds);


/* ft_crate_node.c */

int		ft_infile(char **sub_cmd);
int		ft_outfile(char **sub_cmd);
char 	*ft_cmd(char **sub_cmd);
char	**ft_full_cmd(char **sub_cmd);

/*ft_gest_ambiental.c*/

char	**ft_gest_ambiental(char **spl, char **envp);

/*expand_vars.c*/

char	**expand_vars(char **mat);

/*trim_quotes.c*/

char	**trim_quotes(char **exp);

/*final_split.c*/

char	**final_split(char *input, char **envp);

/*utils1.c*/

int		in_set(char c, char *s);
char	*find_next_char(char *str, char *set, int i);
char	**copy_arrarr(char **arr);
int		compare_env(char *env, char *av, int k, int i);

/*utils2.c*/

int		ft_splitlen(char **split);
char	*ft_strjoin_free(char *s1, char *s2);
char	**ft_add_to_split(char **spl, char *str);
char	**ft_join_split(char **spl1, char **spl2);
char	**ft_subsplit(char **split, int x, int y);

/*utils_print.c*/

void	print_arrarr(char **arr);
void	print_node(t_node *node, char **sub_spl);

/*utils1_free.c*/

void	free_arrarr(char **mat);

/*vik ft*/
char **ft_gest_ambiental(char **av, char **envp);

/*vik ft*/
char **ft_gest_ambiental(char **av, char **envp);

#endif
