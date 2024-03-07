/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:03:05 by rihoy             #+#    #+#             */
/*   Updated: 2024/03/07 15:25:41 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lib_utils.h"
#include "get_next_line.h"

int	main(int argc, const char **argv, const char **env)
{
	// t_shell	bash;
	char	*str;

	if (argv == NULL)
		return (1);
	launch_shell(argc, env);
	while (1)
	{
		// write(1, CY"Minishell >: "RST, 13);
		str = get_next_line(1);
		if (valid_str(str))
			print_error("ok\n");
		else
			print_error("KO\n");
		free(str);
	}
	// cutting((char *)argv[1]);
	// lib_memset(&bash, 0, sizeof(bash));
	// get_true_path(&bash, env);
	// free_split(bash.path);
	return (0);
}
