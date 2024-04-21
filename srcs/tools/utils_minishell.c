/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:37:47 by yrio              #+#    #+#             */
/*   Updated: 2024/04/21 13:30:26 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **env)
{
	char	**path_split;
	char	*path;
	int		tmp;

	if (!env || !env[0])
		return (NULL);
	tmp = 0;
	path = NULL;
	path_split = NULL;
	while (env[tmp])
	{
		if (!ft_strncmp(env[tmp], "PATH=", 5))
		{
			path = ft_substr(env[tmp], 5, ft_strlen(env[tmp]) - 5);
			if (!path)
				exit(0);
		}
		tmp++;
	}
	if (path)
		path_split = ft_split(path, ':');
	if (!path_split)
		exit(0);
	free(path);
	return (path_split);
}

void	malloc_env(t_shell *minishell, char **env)
{
	t_envlist	*new;
	t_envlist	*lst;
	int			tmp;
	int			tmp2;

	if (!env[0])
	{
		minishell->lst_envs = NULL;
		return ;
	}
	tmp = 0;
	while (env[tmp])
		tmp++;
	lst = lst_new((char *)env[0], 1);
	lst->index = 0;
	minishell->lst_envs = lst;
	tmp2 = 1;
	while (tmp2 < tmp)
	{
		new = lst_new((char *)env[tmp2], 1);
		new->index = tmp2;
		lstadd_back(new, lst);
		tmp2++;
	}
}

// Je vais faire une liste chaine avec tout les elements de env qui sont 
// malloc et je vais split la chaine en 2 avec le '=' et il y aura un attribut
// 'key' et un attribut 'value' dans chaque element de ma liste chaine
// Pour la key 'DBUS_SESSION_BUS_ADDRESS' de l'environnement il y a deux egal
// et donc cela pose un probleme avec le split

int	check_cmd_parsing(char *cmd)
{
	if (!cmd)
		return (0);
	else if (cmd[0] == 0)
	{
		write(2, "Command '' not found\n", 22);
		return (0);
	}
	if (cmd[0] == '.' && cmd[1] == '/' && access(cmd, X_OK) == -1)
	{
		printf_error("bash : %s: Permission denied\n", cmd);
		return (0);
	}
	return (1);
}

char	*check_cmd(char *cmd, char **path_split)
{
	char	*path_str;
	char	*path_tmp;
	int		tmp;

	if (!check_cmd_parsing(cmd))
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	tmp = 0;
	while (path_split[tmp])
	{
		path_tmp = str_join(path_split[tmp], "/");
		if (!path_tmp)
			return (NULL);
		path_str = opti_join(path_tmp, cmd);
		if (!path_str)
			return (NULL);
		if (access(path_str, F_OK) == 0)
			return (path_str);
		free(path_str);
		tmp++;
	}
	printf_error("%s : command not found\n", cmd);
	return (NULL);
}

int	check_path(t_shell *bash)
{
	char	**paths_str;
	char	*path_str;
	int		tmp;

	path_str = get_value_env(bash, "PATH");
	if (!path_str)
		return (0);
	paths_str = ft_split(path_str, ':');
	tmp = 0;
	while (paths_str[tmp])
	{
		if (!ft_strcmp(paths_str[tmp], "/bin"))
		{
			free_split(paths_str);
			return (1);
		}
		tmp++;
	}
	free_split(paths_str);
	return (0);
}
