/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lst_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:52:58 by rihoy             #+#    #+#             */
/*   Updated: 2024/04/12 18:27:10 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	calcul_pars(t_token *token, t_shell *bash);
bool	check_token(t_token token, t_shell *bash);

bool	check_lst_split(t_shell *bash)
{
	t_infopars	*curr;
	t_token		token;

	curr = bash->lst_char;
	lib_memset(&token, 0, sizeof(token));
	while (curr)
	{
		if (!finish_quote(curr->str, &token, bash) || \
		!good_operator(curr->str, bash) || !in_feature(curr, bash) || \
		!before_operator(curr, curr->prec, bash) || \
		!after_operator(curr->prec, curr, curr->next, bash) || \
		!check_pars(&curr, &token, bash) || !check_redirection(curr, bash))
		{
			free_boxshell(&bash->lst_char);
			bash->lst_char = NULL;
			return (false);
		}
		if (curr)
			curr = curr->next;
	}
	if (!check_token(token, bash))
		return (false);
	return (true);
}

bool	check_token(t_token token, t_shell *bash)
{
	if (token.in_pars > token.out_pars)
	{
		printf_error(RED" -- Feature not include --\n"RST);
		free_boxshell(&bash->lst_char);
		bash->lst_char = NULL;
		return (false);
	}
	return (true);
}

void	id_shellst(t_shell *bash)
{
	t_infopars	*curr;

	curr = bash->lst_char;
	while (curr)
	{
		if (curr->str[0] == '<' || curr->str[0] == '>')
			curr->spe = 4;
		else if (curr->prec && curr->prec->spe == 4)
			curr->spe = 3;
		else if (is_operator(curr->str[0]))
		{
			if (str_len(curr->str) == 2)
				curr->spe = 1;
			else if (str_len(curr->str) == 1)
				curr->spe = 5;
		}
		else if ((!curr->prec || (curr->prec && curr->prec->spe != 4)) && \
		curr->str[0] != '(' && curr->str[0] != ')')
			curr->spe = 2;
		curr = curr->next;
	}
}

bool	sub_shell(t_infopars *lst, t_shell *bash)
{
	t_infopars	*curr;

	curr = lst;
	while (curr)
	{
		if ((curr->spe == 0 && curr->prec && curr->prec->spe == 5) || \
		(curr->next && curr->next->spe == 5 && curr->spe == 0))
		{
			free_boxshell(&bash->lst_char);
			bash->lst_char = NULL;
			printf_error(RED" -- Subshell not include --\n"RST);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}
