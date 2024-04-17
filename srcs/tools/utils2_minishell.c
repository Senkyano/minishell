/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:21:18 by yrio              #+#    #+#             */
/*   Updated: 2024/04/17 11:53:32 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_word_first(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != c && s[i] != '\0')
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] == c && s[i] != '\0')
	{
		word[i] = s[i];
		i++;
	}
	while (s[i] != c && s[i] != '\0')
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	*ft_word(char const *s)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] != '\0')
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_onedel(char const *s, char c)
{
	char	**char_tab;

	char_tab = (char **)malloc(3 * sizeof(char *));
	if (char_tab == NULL)
		return (NULL);
	if (*s == c)
		s++;
	char_tab[0] = ft_word_first(s, c);
	if (char_tab[0] == NULL)
		return (ft_free(char_tab, 3));
	while (*s != c && *s != '\0')
		s++;
	if (*s)
	{
		s++;
		char_tab[1] = ft_word(s);
		if (char_tab[1] == NULL)
			return (ft_free(char_tab, 3));
		char_tab[2] = 0;
		return (char_tab);
	}
	char_tab[1] = 0;
	return (char_tab);
}

int	check_args(char **args_split, t_shell *minishell)
{
	if (args_split[1] && args_split[1][0] && \
		args_split[1][0] == '-' && args_split[1][1] == '-')
	{
		printf("bash: cd: -%c: invalid option\n", args_split[1][1]);
		minishell->exit_status = 2;
		return (0);
	}
	else if (args_split[1] && args_split[2] && args_split[2][0] != '\n')
		ft_putendl_fd("bash: cd: too many arguments", 2);
	else if (!check_env_key(minishell, "PWD"))
		ft_putendl_fd("minishell : cd: PWD not set", 2);
	else if (!check_env_key(minishell, "OLDPWD"))
		ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
	else if (!check_env_key(minishell, "HOME"))
		ft_putendl_fd("minishell : cd: HOME not set", 2);
	else
		return (1);
	minishell->exit_status = 1;
	return (0);
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

// int		main(void)
// {
// 	char 	*str = "hello==test";
// 	char 	c = '=';
// 	char 	**char_tab;

// 	char_tab = ft_split_onedel(str, c);
// 	printf("%s\n", char_tab[0]);
// 	printf("%s\n", char_tab[1]);
// 	ft_free(char_tab, 2);
// 	return (0);
// }
