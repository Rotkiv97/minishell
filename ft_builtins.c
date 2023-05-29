/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcolucci <dcolucci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 17:18:16 by dcolucci          #+#    #+#             */
/*   Updated: 2023/05/29 16:40:19 by dcolucci         ###   ########.fr       */
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
		if(!(ft_strncmp(node->full_cmd[x], "-n", ft_strlen(node->full_cmd[x]))))
			flag = 1;
		else
		{
			printf("%s", node->full_cmd[x]);
		}
		x++;
	}
	if(flag == 0)
		printf("\n");
	return (1);
}

int	ft_pwd(void)
{
	char *tmp;

	tmp = getcwd(0, 0);
	printf("%s\n", tmp);
	free(tmp);
	return (1);
}

int	ft_env(t_sh *sh)
{
	int x;

	x = 0;
	while(sh->envp[x])
		printf("%s\n", sh->envp[x++]);
	return (1);
}


int	ft_cd(t_node *node, t_sh *shell)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(0, 0);
	if(node->full_cmd[1] == NULL)
	{
		chdir(getenv("HOME"));
		pwd = getcwd(0, 0);
		ft_setenv(shell->envp, "OLDPWD", old_pwd);
		ft_setenv(shell->envp, "PWD", pwd);
		free(pwd);
	}
	else if (node->full_cmd[1] != NULL)
	{	
		if(node->full_cmd[2])
		{
			printf("minishell: cd: too many arguments\n");
			return (1);
		}
		if(chdir(node->full_cmd[1]) == -1)
		{	
			printf("minishell: cd: %s :No such file or directory\n", \
				node->full_cmd[1]);
			return (1);
		}
		else
		{
			pwd = getcwd(0, 0);
			ft_setenv(shell->envp, "OLDPWD", old_pwd);
			ft_setenv(shell->envp, "PWD", pwd);
			free(pwd);
		}
	}
	free(old_pwd);
	return (1);
}

int	ft_export(t_node *node, t_sh *sh)
{
	int		x;
	//char	**tmp;
	//char	*tmp2;
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
			//tmp = sh->envp;
			sh->envp = ft_add_to_split(sh->envp, node->full_cmd[1]);
			//free(tmp);
		}
		else
		{
			trun = ft_truncate_eq(node->full_cmd[1]);
			while(sh->envp[x] != NULL)
			{
				trun_env = ft_truncate_eq(sh->envp[x]);
				if(!(ft_strncmp(trun, trun_env, ft_max(ft_strlen(trun), ft_strlen(trun_env)))))
				{
					//tmp2 = sh->envp[x];
					sh->envp[x] = ft_strdup(node->full_cmd[1]);
					//free(tmp2);
					return (1);
				}
				x++;
			}
			if (sh->envp[x] == NULL)
			{
				//tmp = sh->envp;
				sh->envp = ft_add_to_split(sh->envp, node->full_cmd[1]);
				//free(tmp);
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
				//free(tmp);
				return (1);
			}
			tmp = tmp;
			x++;
		}	
	}
	return (1);
}

int	ft_builtins(t_node *node, t_sh *sh)
{
	int x;

	x = 0;
	if (!node->cmds)
		return (0);
	if(node->full_cmd[x])
	{
		if (!(ft_strncmp(node->full_cmd[x], "echo", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("echo")))))
			return (ft_echo(node));
		else if (!(ft_strncmp(node->full_cmd[x], "pwd", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("pwd")))))
			return(ft_pwd());
		else if (!(ft_strncmp(node->full_cmd[x], "exit", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("exit")))))
			exit(0);
		else if (!(ft_strncmp(node->full_cmd[x], "env", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("env")))))
			return(ft_env(sh));
		else if (!(ft_strncmp(node->full_cmd[x], "cd", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("cd")))))
			return(ft_cd(node, sh));
		else if (!(ft_strncmp(node->full_cmd[x], "export", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("export")))))
			return(ft_export(node, sh));
		else if (!(ft_strncmp(node->full_cmd[x], "unset", ft_max(ft_strlen(node->full_cmd[x]), ft_strlen("unset")))))
			return(ft_unset(node, sh));
	}
	return(0);
}