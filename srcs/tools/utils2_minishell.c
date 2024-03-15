/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:21:18 by yrio              #+#    #+#             */
/*   Updated: 2024/03/15 12:38:35 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static int	count_words(char const *s, char c)
{
	int	part;
	int	count;

	part = 0;
	count = 0;
	while (*s != '\0')
	{
		if (*s == c && !count && *s != '\0')
		{
			s++;
			count = 1;
		}
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
			part++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (part);
}

static char	*ft_word(char const *s, char c)
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

char	**ft_split_onedel(char const *s, char c)
{
	char	**char_tab;
	int		i;
	int		nb_words;

	nb_words = count_words(s, c);
	char_tab = (char **)malloc((nb_words + 1) * sizeof(char *));
	if (char_tab == NULL)
		return (NULL);
	i = 0;
	while (*s && i < nb_words)
	{
		if (*s == c)
			s++;
		char_tab[i] = ft_word(s, c);
		if (char_tab[i] == NULL)
			return (ft_free(char_tab, nb_words));
		i++;
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
			s++;
	}
	char_tab[i] = 0;
	return (char_tab);
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
