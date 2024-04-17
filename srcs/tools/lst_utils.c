/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:46:38 by yrio              #+#    #+#             */
/*   Updated: 2024/04/17 13:43:05 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*lst_new(char *str, int display)
{
	t_envlist	*new;
	char		**splitting;

	new = malloc(sizeof(t_envlist));
	if (!new)
		exit(0);
	splitting = ft_split_onedel(str, '=');
	if (splitting[0] && splitting[1] && splitting[2])
		printf("splitting : %s\n", splitting[2]);
	if (!splitting)
		exit(0);
	new->key = splitting[0];
	if (splitting[0])
		new->value = splitting[1];
	else
		new->value = NULL;
	new->display = display;
	new->splitting = splitting;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_envlist *new, t_envlist *lst)
{
	t_envlist	*tmp;

	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	lstclear(t_envlist *lst)
{
	t_envlist	*first;
	t_envlist	*second;

	if (lst == NULL)
		return ;
	first = lst;
	while (first != NULL)
	{
		second = first;
		first = first -> next;
		free_split(second->splitting);
		free(second);
	}
	lst = NULL;
}

t_lstcmd	*lst_index(t_lstcmd *lst, int index)
{
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		if (lst->index == index)
			return (lst);
		lst = lst -> next;
	}
	return (NULL);
}

int	lst_size(t_lstcmd *lstcmd)
{
	int	size;

	if (lstcmd == NULL)
		return (0);
	size = 0;
	while (lstcmd)
	{
		size++;
		lstcmd = lstcmd->next;
	}
	return (size);
}
