/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:27:47 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/13 19:20:55 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

char	*env_value(char *str, t_envlist *lst_envs, int i);
int		name_env(char *str);

char	*insert_env(char *str, t_shell *bash)
{
	char	*new_str;
	char	*tmp;
	int		i;

	i = 0;
	new_str = NULL;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] != '$')
		{
			tmp = strup_to(str + i, skip_not_env(str + i));
			if (!tmp)
				return (NULL);
			i += skip_not_env(str + i);
		}
		else if (str[i] == '$')
		{
			i++;
			new_str = opti_join(new_str, env_value(str + i, bash->lst_envs, name_env(str + i)));
			if (!new_str)
				return (NULL);
			i += name_env(str + i);
		}
		if (!new_str && tmp)
		{
			new_str = lib_strup(tmp);
			if (!new_str)
				return (NULL);
			free(tmp);
			tmp = NULL;
		}
		else if (new_str && tmp)
		{
			new_str = str1_join(new_str, tmp);
			if (!new_str)
				return (NULL);
		}
	}
	free(str);
	return (new_str);
}

char	*env_value(char *str, t_envlist *lst_envs, int i)
{
	t_envlist	*curr;
	
	curr = lst_envs;
	while (curr)
	{
		if (str_ncmp(str, curr->key, i) && str_len(curr->key) == i)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int	name_env(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && (is_char(str[i]) || is_num(str[i])))
	{
		i++;
		len++;
	}
	return (len);
}
