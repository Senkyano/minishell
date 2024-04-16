/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:29:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/16 22:17:38 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_utils.h"
#include <stdlib.h>
#include <unistd.h>

char	*str_join(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = malloc((str_len(str1) + str_len(str2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		new_str[i + j] = str2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

char	*opti_join(char *str1, char *str2)
{
	t_data_lib	data;

	lib_memset(&data, 0, sizeof(data));
	data.x = -1;
	data.i = -1;
	if (!str1)
	{
		str1 = lib_strup("");
		data.trig = 1;
		if (!str1)
			return (NULL);
	}
	if (!str2)
		return (str1);
	data.new_str = malloc((str_len(str1) + str_len(str2) + 1 * sizeof(char)));
	if (!data.new_str)
		return (NULL);
	while (str1[++data.i])
		data.new_str[data.i] = str1[data.i];
	while (str2[++data.x])
		data.new_str[data.i++] = str2[data.x];
	data.new_str[data.i] = '\0';
	free(str1);
	return (data.new_str);
}

char	*str1_join(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!str1)
	{
		str1 = malloc(1 * sizeof(char));
		if (!str1)
			return (NULL);
		str1[0] = '\0';
	}
	new_str = malloc((str_len(str1) + str_len(str2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		new_str[i] = str1[i];
	while (str2[++j])
		new_str[i++] = str2[j];
	new_str[i] = '\0';
	free(str1);
	return (new_str);
}

char	*str2_join(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	new_str = malloc((str_len(str1) + str_len(str2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		new_str[i] = str1[i];
	while (str2[++j])
		new_str[i + j] = str2[j];
	new_str[i + j] = '\0';
	free(str2);
	return (new_str);
}

char	*strall_join(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	if (!str1)
	{
		str1 = lib_strup("");
		if (!str1)
			return (NULL);
	}
	if (!str2)
	{
		str2 = lib_strup("");
		if (!str2)
			return (NULL);
	}
	new_str = malloc((str_len(str1) + str_len(str2) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i] != 0)
		new_str[i] = str1[i];
	while (str2[++j] != 0)
		new_str[i + j] = str2[j];
	new_str[i + j] = '\0';
	free(str2);
	free(str1);
	return (new_str);
}
