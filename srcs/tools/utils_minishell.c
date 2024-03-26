/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:37:47 by yrio              #+#    #+#             */
/*   Updated: 2024/03/26 16:26:57 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell_exec.h"

void	ls_cmd(void)
{
	char *dir_path;
	DIR* rep;
	struct dirent* fichierLU;

	dir_path = NULL;
	rep = NULL;
	fichierLU = NULL;
	dir_path = getcwd(dir_path, PATH_MAX);
	rep = opendir(dir_path);
	if (!rep)
		exit(1);
	fichierLU = readdir(rep);
	while (fichierLU)
	{
		ft_putstr_fd(fichierLU->d_name, 1);
		ft_putchar(' ');
		fichierLU = readdir(rep);
	}
	ft_putchar('\n');
	if (closedir(rep) == -1)
		exit(-1);
	free(dir_path);
}

char	**get_paths(char **env)
{
	char	**path_split;
	char	*path;
	int		tmp;

	if (!env[0])
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
	path_split = ft_split(path, ':');
	if (!path_split)
		exit(0);
	free(path);
	return (path_split);
}

char	**free_split(char **char_tab)
{
	int	tmp;

	tmp = 0;
	while (char_tab[tmp])
		free(char_tab[tmp++]);
	free(char_tab);
	return (NULL);
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
	lst = lst_new((char *)env[0]);
	lst->index = 0;
	minishell->lst_envs = lst;
	tmp2 = 1;
	while (tmp2 < tmp)
	{
		new = lst_new((char *)env[tmp2]);
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

char	*check_cmd(char *cmd, char **path_split)
{
	char	*path_str;
	int		tmp;

	if (cmd == NULL)
	{
		write(2, "Command '' not found\n", 22);
		return (NULL);
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	tmp = 0;
	while (path_split[tmp])
	{
		path_str = ft_strjoin_gnl(ft_strjoin(path_split[tmp], "/"), cmd, ft_strlen(cmd));
		if (access(path_str, F_OK) == 0)
			return (path_str);
		free(path_str);
		tmp++;
	}
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	return (NULL);
}
