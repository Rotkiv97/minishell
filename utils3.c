/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:05:42 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/29 16:32:37 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export(char *str, char *env)
{
	int	x;

	x = 0;
	while (env[x] && env[x] != '=')
		x++;
	return (ft_strncmp(str, env, x));
}

char *ft_truncate_eq(char *str)
{
	int		x;
	char	*trun;

	if (!str)
		return (0);
	if (!ft_strchr(str, '='))
		return (str);
	x = 0;
	while (str[x] && str[x] != '=')
		x++;
	trun = (char *) malloc (sizeof(char) * (x + 1));
	ft_strlcpy(trun, str, x + 1);
	return (trun);
}

void	ft_setenv(char **envp, char *var, char *value)
{
	int		x;
	char	*trun_env;
	//char	*tmp;
	char	*tmp_join;
	char	*join;

	x = 0;
	if (!envp || !var || !value)
		return ;
	while (envp[x])
	{
		trun_env = ft_truncate_eq(envp[x]);
		if (!ft_strncmp(trun_env, var, ft_max(ft_strlen(trun_env), ft_strlen(var))))
		{
			//tmp = envp[x];
			tmp_join = ft_strjoin(var, "=");
			//free(var);
			join = ft_strjoin(tmp_join, value);
			//free(tmp_join);
			envp[x] = join;
			//free(tmp);
		}
		x++;
	}
}