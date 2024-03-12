/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/12 17:44:28 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "lib_utils.h"

static bool	start_process(char *str, t_shell *bash);
// static bool	lst_shellstr(t_shell *bash);

void	build_process(char *str, t_shell *bash)
{
	if (!start_process(str, bash))
		return ;
	// if (!lst_shellstr(bash))
	// 	return ;
	// free_strshell(&bash->lst_char);
}

// static bool	lst_shellstr(t_shell *bash)
// {
// 	int			i;
// 	t_infopars	*tmp;

// 	i = -1;
// 	while (bash->str_split[++i])
// 	{
// 		tmp = diff_strshell(bash->str_split[i], 1);
// 		if (!tmp)
// 		{
// 			printf_error(CY"Minishell >: "RED"Malloc fail\n"RST);
// 			free_split(bash->str_split);
// 			return (false);
// 		}
// 		add_strshell(&bash->lst_char, tmp);
// 	}
// 	free_split(bash->str_split);
// 	return (true);
// }

static bool	start_process(char *str, t_shell *bash)
{
	if (!valid_str(str))
	{
		printf_error(CY"Minishell >: "RED"Invalid process\n"RST);
		return (false);
	}
	bash->str_split = split_minishell(str);
	if (!bash->str_split)
	{
		printf_error(CY"Minishell >: "RED"Malloc fail\n"RST);
		return (false);
	}
	int	i;

	i = 0;
	while (bash->str_split[i])
	{
		printf("%s ", bash->str_split[i]);
		i++;
	}
	lib_free_split(bash->str_split);
	return (true);
}
