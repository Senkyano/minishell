/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openning_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:02 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/15 22:58:17 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(t_infopars *curr, t_shell *bash, int fd[2]);
bool	gestion_close(int fd[2], pid_t *heredoc, t_shell *bash, t_infopars *curr);

// Ouvrir tout les fichier de type heredoc

bool	open_heredoc(t_infopars *lstchar, t_lstcmd *cmd, t_shell *bash, int def)
{
	t_infopars	*curr;
	pid_t		heredoc;
	int			fd[2];

	curr = lstchar;
	lib_memset(fd, 0, sizeof(fd));
	while (curr && curr->spe != 5)
	{
		if (curr->spe == 4 && curr->str[0] == '<' && str_len(curr->str) == 2)
		{
			if (!gestion_close(fd, &heredoc, bash, curr))
				return (false);
			cmd->in_file = fd[0];
			close(fd[1]);
			wait(NULL);
		}
		curr = curr->next;
	}
	if (def == HERE_DOC)
		cmd->in_file = fd[0];
	else
		close(fd[0]);
	return (true);
}

bool	gestion_close(int fd[2], pid_t *heredoc, t_shell *bash, t_infopars *curr)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 0)
		close(fd[1]);
	if (pipe(fd) < 0)
	{
		printf_error(RED"pipe failed\n"RST);
		return (false);
	}
	*heredoc = fork();
	if (*heredoc == -1)
	{
		printf_error(RED"fork failed\n"RST);
		return (false);
	}
	else if (*heredoc == 0)
		write_heredoc(curr, bash, fd);
	return (true);
}

static void	write_heredoc(t_infopars *curr, t_shell *bash, int fd[2])
{
	char	*str;

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
	eradication(bash, 0);
}

//definir si il y a un fichier d'entree ou de sortie

void	def_file(t_infopars *lst_char, t_lstcmd *cmd, int def)
{
	t_infopars	*curr;

	curr = last_infile(lst_char);
	if (curr && def == NO_HERE_DOC)
	{	
		if (curr->prec->str[0] == '<' && str_len(curr->prec->str) == 1)
			cmd->in_file = open(curr->str, O_RDONLY);
	}
	curr = last_outfile(lst_char);
	if (curr)
	{
		if (str_len(curr->prec->str) == 1)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (str_len(curr->prec->str) == 2)
			cmd->out_file = open(curr->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

//definir le dernier fichier d'entree

bool	define_last(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst_char;
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
	def_file(lst_char, cmd, cmd->last_infile);
	if (!open_heredoc(lst_char, cmd, bash, cmd->last_infile))
		return (false);
	return (true);
}
