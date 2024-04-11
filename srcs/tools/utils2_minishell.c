/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:21:18 by yrio              #+#    #+#             */
/*   Updated: 2024/04/09 15:56:46 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_words(char const *s, char c)
// {
// 	int	part;
// 	int	count;

// 	part = 0;
// 	count = 0;
// 	while (*s != '\0')
// 	{
// 		if (*s == c && !count && *s != '\0')
// 		{
// 			s++;
// 			count = 1;
// 		}
// 		while (*s == c && *s != '\0')
// 			s++;
// 		if (*s != c && *s != '\0')
// 			part++;
// 		while (*s != c && *s != '\0')
// 			s++;
// 	}
// 	return (part);
// }

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
