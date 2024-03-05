/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/05 19:28:25 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

// static int	skip_space(char *str);

// void	get_all_process(char *process, t_shell *bash)
// {
// 	int	i;

// 	i = -1;
// 	bash->space = 
// 	while (bash->space[++i])
// 	{
// 	// analyse du space.
// 		//regarder si le premier c'est une cmd.
// 		// puis regarder si cest des fichier valide
// 	// Dans le get process on auras d'abord le get_all_cmd.
// 		// Je vais devoir faire un split entre pipe
// 	}
// }

int	cutting(char *str, t_lstcmd *base)
{
	int			i;
	t_token		token;
	t_lstcmd	*tmp;

	lib_memset(&token, 0, sizeof(token));
	token.in_cmd = true;
	i = 0;
	while (str[i])
	{
		i += skip_space(str + i);
					
		// i += cutting(str + i, base); la recursive se feras appelle que pour or/and
	}
}

// static	void	id_main_process(t_token *token, char *str)
// {
// 	int	i;

// 	i  = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] && str[i])
// 	}
// }

// static int	skip_space(char *str)
// {
// 	int	i;
	
// 	i = 0;
// 	while (str[i] && (str[i] == 32 || str[i] == 11))
// 		i++;
// 	return (i);	
// }
