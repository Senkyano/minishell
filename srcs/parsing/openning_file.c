/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openning_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/12 18:20:17 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ouvrir tout les fichier de type heredoc

bool	write_here(pid_t *here ,int fd[2], char *lim, t_shell *bash)
{
	char	*line;

	*here = fork();
	if (here < 0)
	{
		if (fd[0] != 0)
			close(fd[0]);
		if (fd[1] != 0)
			close(fd[1]);
		printf_error(RED"error: fork failed\n"RST);
		return (false);
	}
	else if (here == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line || !slib_cmp(line, lim))
				eradication(bash, fd[1]);
			write(fd[1], line, sizeof(line));
			write(fd[1], "\n", 1);
		}
	}
	return (true);
}

bool	open_heredoc(t_infopars	*lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;
	int			pipefd[2];
	pid_t		here;

	curr = lst_char;
	here = 0;
	lib_memset(pipefd, 0, sizeof(int));
	while (curr)
	{
		if (curr->spe == 3 && curr->prec->str[0] == '<' && \
		str_len(curr->prec->str) == 2)
		{
			if (cmd->in_file != 0)
				close(cmd->in_file);
			if (pipe(pipefd))
			{
				bash->exit_status = 127;					
				return (false);
			}
			cmd->in_file = pipefd[0];
			if (!write_here(&here, pipefd, curr->str, bash))
				return (false);
			close(pipefd[1]);
			waitpid(here, NULL, 0);
		}
		curr = curr->next;
	}
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
			bash->exit_status = 127;
			return (false);
		}
	}
	return (true);
}

//definir le dernier fichier d'entree

void	define_last_in(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
	def_file(lst_char, cmd, bash);
	while (curr && curr->spe != 5 && curr->spe != 1 && curr->spe != 0)
	{
		if (curr->spe == 3 && curr->str[0] == '<')
		{
			if (str_len(curr->str) == 1)
				cmd->last_infile = NO_HERE_DOC;
			else if (str_len(curr->str) == 2)
				cmd->last_infile = HERE_DOC;
		}
		curr = curr->next;
	}
}
