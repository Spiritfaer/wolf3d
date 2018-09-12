/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:47:36 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/09 16:47:37 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int8_t		ft_check_texture(int16_t wall)
{
	if (wall >= greystone && wall <= pillar)
		return (1);
	return (0);
}

int8_t		ft_check_sprite(int16_t wall)
{
	if (wall >= barrel && wall <= pillar)
		return (1);
	return (0);
}

int8_t		ft_check_w_map(t_list *head, int16_t map_w)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (map_w != (int16_t)ft_splitter(tmp->content, ' '))
			return (ft_errors("error incorect map_w!\n"));
		tmp = tmp->next;
	}
	return (1);
}
