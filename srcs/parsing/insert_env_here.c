/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env_here.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:33:13 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/18 13:58:58 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_not_env_here(char *str);

char	*insert_env_here(char *str, t_shell *bash)
{
	t_data	x;
	int		i;

	i = 0;
	lib_memset(&x, 0, sizeof(x));
	x.new_str = NULL;
	while (str[i])
	{
		if (str[i] != '$')
		{
			x.tmp = strup_to(str + i, skip_not_env_here(str + i));
			if (!x.tmp)
				return (NULL);
			i += skip_not_env_here(str + i);
		}
		else if (str[i++] == '$')
		{
			take_value(str + i, bash, &x);
			i += name_env(str + i);
		}
		if (!join_tmp(&x))
			return (NULL);
	}
	return (free(str), x.new_str);
}

static int	skip_not_env_here(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '$' && str[i])
	{
		i++;
	}
	return (i);
}

int	change_(char *str, t_shell *bash, t_data *x, t_token *token)
{
	int	len;

	len = 0;
	in_doquote(*str, token);
	in_sgquote(*str, token);
	if (*str != '$')
	{
		len = skip_not_env(str, token);
		x->tmp = strup_to(str, len);
		if (!x->tmp)
			return (-1);
		return (len);
	}
	else if (*str == '$' && !token->in_sgquote)
	{	
		len++;
		if (!take_value(str + len, bash, x))
			return (-1);
		len += name_env(str + len);
		return (len);
	}
	return (len);
}
