/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:51:53 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 10:51:55 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		ft_print_list(t_list *head)
{
	while (head)
	{
		printf("%s\n", (char*)head->content);
		head = head->next;
	}
}

void		ft_split_del(char **head)
{
	uint_fast32_t	i;

	i = 0;
	while (head[i])
	{
		free(head[i]);
		head[i] = NULL;
		i++;
	}
	free(head);
	head = NULL;
}

void		ft_list_del(t_list **head)
{
	t_list *tmp;

	while ((*head))
	{
		tmp = (*head);
		(*head) = (*head)->next;
		if (tmp->content)
			free(tmp->content);
		tmp->content = NULL;
		tmp->content_size = 0;
		free(tmp);
	}
}

void		ft_revers_list(t_list **head)
{
	t_list			*prev;
	t_list			*current;
	t_list			*next;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

uint32_t	ft_count_list(t_list *head)
{
	uint32_t	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
