/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:03:05 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/08 17:12:01 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"
#include "get_next_line.h"

void	init_shell(t_shell *bash);

int	main(int argc, const char **argv, const char **env)
{
	t_shell	bash;
	char	*str;

	if (argv == NULL)
		return (1);
	lib_memset(&bash, 0, sizeof(bash));
	launch_shell(argc, env);
	printf_error(CY"Minishell >: "RST);
	str = get_next_line(1);
	while (str)
	{
		if (valid_str(str))
			build_process(str, &bash);
		else
			printf_error(RED"-- Feature not include --\n"RST);
		free(str);
		printf_error(CY"Minishell >: "RST);
		str = get_next_line(1);
	}
	return (0);
}

void	init_shell(t_shell *bash)
{
	bash->exit_status = 0;
	bash->path = NULL;
	bash->nbr_path = 0;
	bash->env = NULL;
	bash->str_split = NULL;
	bash->lstcmd = NULL;
	bash->lst_char = NULL;
}
