/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:41:17 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 10:41:18 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		print_arg(t_arg ar)
{
	printf("m_t - %s\nWidth - %d\nHeight - %d\n",
			ar.map_name, ar.screen_w, ar.screen_h);
	if (ar.flag & MAPN)
		printf("Map + ");
	else
		printf("Map - ");
	if (ar.flag & MAPW)
		printf("Width + ");
	else
		printf("Width - ");
	if (ar.flag & MAPH)
		printf("Height +\n");
	else
		printf("Height -\n");
}

void		ft_print_map(t_map *map_t)
{
	t_v2i	i;

	i.x = 0;
	i.y = 0;
	while (i.y < map_t->map_h)
	{
		i.x = 0;
		while (i.x < map_t->map_w)
		{
			printf("%d ", map_t->map[i.y][i.x]);
			i.x++;
		}
		printf("\n");
		i.y++;
	}
}

t_list		*ft_smooth(t_list **head)
{
	t_list *next;

	next = (*head)->next;
	if ((*head)->content)
		free((*head)->content);
	(*head)->content_size = 0;
	free(*head);
	return (next);
}

void		ft_sort(void **sorted, int16_t size)
{
	t_spr	*one;
	int16_t	i;
	int16_t	j;
	t_spr	tmp;

	one = (t_spr *)sorted;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		{
			while (j < size - 1)
			{
				if (one[j].dist < one[j + 1].dist)
				{
					tmp = one[j];
					one[j] = one[j + 1];
					one[j + 1] = tmp;
				}
				j++;
			}
			i++;
		}
	}
}

SDL_Color	get_color(uint32_t in_c)
{
	SDL_Color	color;

	color.r = (uint8_t)((in_c >> 16) & 0xFF);
	color.g = (uint8_t)((in_c >> 8) & 0xFF);
	color.b = (uint8_t)((in_c) & 0xFF);
	color.a = 0;
	return (color);
}
