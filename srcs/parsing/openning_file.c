/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openning_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/17 13:43:21 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ouvrir tout les fichier de type heredoc

bool	open_heredoc(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;
	pid_t		heredoc;
	int			fd[2];
	char		*str;

	curr = lst_char;
	lib_memset(fd, 0, sizeof(fd));
	(void)bash;
	while (curr && curr->spe != 5)
	{
		if (curr->spe == 4 && curr->str[0] == '<' && str_len(curr->str) == 2)
		{
			if (fd[0] != 0)
				close(fd[0]);
			if (fd[1] != 0)
				close(fd[1]);
			if (pipe(fd) < 0)
				return (false);
			heredoc = fork();
			if (heredoc < 0)
			{
				printf_error(RED"fork failed\n"RST);
				return (false);
			}
			else if (heredoc == 0)
			{
				init_signal_child();
				close(fd[0]);
				while (1)
				{
					str = readline(PUR"> "RST);
					if (!str)
						break ;
					if (slib_cmp(str, curr->next->str))
					{
						free(str);
						break ;
					}
					write(fd[1], str, str_len(str));
					write(fd[1], "\n", 2);
					free(str);
				}
				close(fd[1]);
				eradication(bash);
				exit(0);
			}
			cmd->in_file = fd[0];
			close(fd[1]);
			wait(NULL); // wait for the child to finish
		}
		curr = curr->next;
	}
	cmd->in_file = fd[0];
	return (true);
}

//definir si il y a un fichier d'entree ou de sortie

bool	def_file(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = last_infile(lst_char);
	if (curr)
	{	
		if (curr->prec->str[0] == '<' && str_len(curr->prec->str) == 1)
		{
			cmd->in_file_name = lib_strup(curr->str);
			if (!cmd->in_file_name)
				return (false);
		}
	}
	curr = last_outfile(lst_char);
	if (curr)
	{
		if (str_len(curr->prec->str) == 1)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (str_len(curr->prec->str) == 2)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd->out_file < 0)
		{
			printf_error(RED"Max file descriptor reached\n"RST);
			bash->exit_status = 127;
			return (false);
		}
	}
	return (true);
}

//definir le dernier fichier d'entree

bool	define_last(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	if (!def_file(lst_char, cmd, bash))
		return (false);
	if (!open_heredoc(lst_char, cmd, bash))
		return (false);
	while (curr && curr->spe != 5 && curr->spe != 1 && curr->spe != 0)
	{
		if (curr->spe == 4 && curr->str[0] == '<')
		{
			if (str_len(curr->str) == 1)
				cmd->last_infile = NO_HERE_DOC;
			else if (str_len(curr->str) == 2)
				cmd->last_infile = HERE_DOC;
		}
		curr = curr->next;
	}
	return (true);
}
