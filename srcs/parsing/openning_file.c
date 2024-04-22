/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openning_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:04:05 by yrio              #+#    #+#             */
/*   Updated: 2024/04/22 13:52:02 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc(t_infopars *curr, t_shell *bash, int fd[2], t_tree *branch);
bool	gestion_close(int fd[2], t_shell *bash, t_infopars *curr, t_tree *branch);

// Ouvrir tout les fichier de type heredoc

bool	open_heredoc(t_infopars *lstchar, t_lstcmd *cmd, t_shell *bash, t_tree *branch)
{
	t_infopars	*curr;
	int			fd[2];

	curr = lstchar;
	lib_memset(fd, 0, sizeof(fd));
	while (curr && curr->spe != 5 && curr->spe != 1 && curr->spe != 0)
	{
		if (bash->exit_status == 130)
			return (false);
		if (curr->spe == 4 && curr->str[0] == '<' && str_len(curr->str) == 2)
		{
			if (!gestion_close(fd, bash, curr, branch))
				return (false);
			cmd->in_file = fd[0];
			close(fd[1]);
		}
		curr = curr->next;
	}
	if (cmd->last_infile == HERE_DOC)
		cmd->in_file = fd[0];
	else if (fd[0] != 0 && cmd->last_infile == NO_HERE_DOC)
		close(fd[0]);
	return (true);
}

bool	gestion_close(int fd[2], t_shell *bash, t_infopars *curr, t_tree *branch)
{
	int			status;
	pid_t		heredoc;

	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 0)
		close(fd[1]);
	if (pipe(fd) < 0)
	{
		printf_error(RED"pipe failed\n"RST);
		return (false);
	}
	init_signal_ign();
	heredoc = fork();
	if (heredoc == -1)
	{
		printf_error(RED"fork failed\n"RST);
		return (false);
	}
	else if (heredoc == 0)
		write_heredoc(curr, bash, fd, branch);
	waitpid(heredoc, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		bash->exit_status = WEXITSTATUS(status);
	return (true);
}

static void	write_heredoc(t_infopars *curr, t_shell *bash, int fd[2], t_tree *branch)
{
	char		*str;
	char		*lim;

	close_out_heredoc(bash, fd[0], branch->lst_cmd);
	lim = lib_strup(curr->next->str);
	eradication(bash, branch);
	init_signal_here();
	while (1)
	{
		str = readline(PUR"> "RST);
		if (!str)
			break ;
		if (slib_cmp(str, lim))
		{
			free(str);
			break ;
		}
		// str = insert_env_here(str, bash);
		write(fd[1], str, str_len(str));
		free(str);
		write(fd[1], "\n", 2);
	}
	free(lim);
	close(fd[1]);
	exit(0);
}

//definir si il y a un fichier d'entree ou de sortie

bool	def_file(t_infopars *lst_char, t_lstcmd *cmd, int def)
{
	t_infopars	*curr;

	curr = last_infile(lst_char);
	if (curr && def == NO_HERE_DOC)
	{	
		if (curr->prec->str[0] == '<' && str_len(curr->prec->str) == 1)
			cmd->in_file = open(curr->str, O_RDONLY);
	}
	last_outfile(lst_char, cmd);
	return (true);
}

//definir le dernier fichier d'entree

bool	define_last(t_infopars *lst_char, t_lstcmd *cmd, t_shell *bash, t_tree *branch)
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
	if (!def_file(lst_char, cmd, cmd->last_infile))
		return (false);
	if (!open_heredoc(lst_char, cmd, bash, branch))
		return (false);
	return (true);
}
