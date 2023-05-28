/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:18:16 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/28 19:48:52 by dcolucci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_node *node)
{
	int x;
	int flag;

	flag = 0;
	x = 1;
	while(node->full_cmd[x])
	{
		//printf("%s\n", node->full_cmd[x]);
		if(!(ft_strncmp(node->full_cmd[x], "-n", ft_strlen(node->full_cmd[x]))))
			flag = 1;
		else
		{
			printf("%s", node->full_cmd[x]);
			//flag = 0;
		}
		x++;
	}
	if(flag == 0)
		printf("\n");
	return (1);
}

int	ft_pwd(t_node *node)
{
	int x;

	x = 0;
	
	node->full_cmd[x] = getcwd(NULL, 0);
	getcwd(node->full_cmd[x], sizeof(node->full_cmd[x]));
	printf("%s----\n", node->full_cmd[x]);
	return (1);
}

int	ft_env(t_sh *sh)
{
	int x;

	x = 0;
	while(sh->envp[x])
	{
		//printf("\033[32m%s\033[0m\n", sh->envp[x]);
		if(!(ft_strncmp(sh->envp[x], "EXPORT", 6)))
			printf("expot\n");
		x++;
	}
	return (1);
}

int	ft_check_cd(char *node)
{
	int x;
	int flag;

	flag = 0;
	x = 0;
	while (node[x])
	{
		if (node[x] == '.')
		{
			if (node[x + 1] == '.')
			{
				if (node[x + 2] == '.')
				{
					flag = 1;
					break;
				}
			}
			x++;	
		}
		else 
			x++;
	}
	if(flag == 1)
		printf("\033[31mci hai provato troglodita\033[0m\n");
	return (1);
}

int	ft_cd(t_node *node)
{
	int x;
	int y;

	x  = 0;
	y = 0;
	if(node->full_cmd == NULL)
		return (1);
	while(node->full_cmd[x])
	{
		if(node->full_cmd[1] == NULL)
		{
			access(node->full_cmd[x], R_OK);
			chdir(getenv("HOME"));
		}
		else if (node->full_cmd[1] != NULL)
		{

			if(node->full_cmd[1][y] == '.')
			{
				ft_check_cd(node->full_cmd[1]);
				chdir(node->full_cmd[x]);
			}
			else if (node->full_cmd[x][y] == '/')
				y++;
			else if(access(node->full_cmd[x], R_OK) == 0)
				chdir(node->full_cmd[x]);
			y++;
		}
		else	
			return (1);
		x++;
	}
	ft_pwd(node);
	return (1);
}

int	ft_export(t_node *node, t_sh *sh)
{
	int		x;
	char	**tmp;
	char	*tmp2;
	char	*trun;
	char	*trun_env;

	x = 0;
	while(sh->envp[x] != NULL && !node->full_cmd[1] )
	{
		printf("declare -x ");
		printf("%s\n", sh->envp[x]);
		x++;
	}
	x = 0;
	if(node->full_cmd[1])
	{
		if(!(ft_strchr(node->full_cmd[1], '=')))
		{
			while(sh->envp[x] != NULL)
			{
				if(!(ft_strncmp(node->full_cmd[1],sh->envp[x],ft_strlen(node->full_cmd[1]))))
					return (1);
				x++;
			}
			tmp = sh->envp;
			sh->envp = ft_add_to_split(sh->envp, node->full_cmd[1]);
			//free(tmp);
		}
		else
		{
			trun = ft_truncate_eq(node->full_cmd[1]);
			while(sh->envp[x] != NULL)
			{
				trun_env = ft_truncate_eq(sh->envp[x]);
				printf("%s", trun_env);
				printf("\n");
				if(!(ft_strncmp(trun, trun_env, ft_max(ft_strlen(trun), ft_strlen(trun_env)))))
				{
					tmp2 = sh->envp[x];
					sh->envp[x] = ft_strdup(node->full_cmd[1]);
					free(tmp2);
					return (1);
				}
				x++;
			}
			if (sh->envp[x] == NULL)
			{
				tmp = sh->envp;
				sh->envp = ft_add_to_split(sh->envp, node->full_cmd[1]);
				free(tmp);
			}
		}
	}
	return (1);
}

int	ft_unset(t_node *node, t_sh *sh)
{
	char	*trun_env;
	int		x;
	char	**s1;
	char	**s2;
	char	**tmp;

	if (!node->full_cmd[1])
	{
		printf("\033[31munset : not enough arguments\033\n");
		return (1);
	}
	else if (ft_strchr(node->full_cmd[1], '='))
	{
		printf("\033[31munset : %s : invalid parameter name\033\n", node->full_cmd[1]);
		return (1);
	}
	else
	{
		while (sh->envp[x])
		{
			trun_env = ft_truncate_eq(sh->envp[x]);
			if (!ft_strncmp(node->full_cmd[1], trun_env, ft_max(ft_strlen(node->full_cmd[1]), ft_strlen(trun_env))))
			{
				tmp = sh->envp;
				s1 = ft_subsplit(sh->envp, 0, x);
				s2 = ft_subsplit(sh->envp, x + 1, INT_MAX);
				sh->envp = ft_join_split(s1, s2);
				free(tmp);
				return (1);
			}
			x++;
		}	
	}
	return (1);
}

int	ft_builtins(t_node *node, t_sh *sh)
{
	int x;

	x = 0;
	if(node->full_cmd[x])
	{
		if (!(ft_strncmp(node->full_cmd[x], "echo", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("echo")))))
			return (ft_echo(node));
		else if (!(ft_strncmp(node->full_cmd[x], "pwd", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("pwd")))))
			return(ft_pwd(node));
		else if (!(ft_strncmp(node->full_cmd[x], "exit", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("exit")))))
			exit(0);
		else if (!(ft_strncmp(node->full_cmd[x], "env", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("env")))))
			return(ft_env(sh));
		else if (!(ft_strncmp(node->full_cmd[x], "cd", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("cd")))))
			return(ft_cd(node));
		else if (!(ft_strncmp(node->full_cmd[x], "export", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("export")))))
			return(ft_export(node, sh));
		else if (!(ft_strncmp(node->full_cmd[x], "unset", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("unset")))))
			return(ft_unset(node, sh));
	}
	return(0);
}