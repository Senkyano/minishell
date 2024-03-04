/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:36:59 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/04 18:34:00 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"

static int	skip_space(char *str);
static int	skip_char(char *str);

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

void	cutting(char *str)
{
	int			i;
	// t_token		token;
	// char		**process;

	// process = NULL;
	// lib_memset(&token, 0, sizeof(token));
	i = 0;
	while (str[i])
	{
		i += skip_space(str + i);
		// printf("%d %s\n", i, (str + i));
		if (str[i])
			i += skip_char(str + i);
	}
}

static int	skip_char(char *str/*, t_token *token*/)
{
	int	i;
	
	i = 0;
	// if (token->)
	while (str[i] && str[i] != 32 && str[i] != 11)
		i++;
	return (i);	
}

static int	skip_space(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && (str[i] == 32 || str[i] == 11))
		i++;
	return (i);	
}
