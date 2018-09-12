/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:35:24 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:35:24 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		ft_remap(t_map *map_t)
{
	char	**str;
	t_v2i	point;
	t_list	*tmp;

	tmp = map_t->head;
	if (!tmp || !(map_t->map = (int16_t**)malloc(sizeof(int16_t*)
												* (map_t->map_h + 1))))
		return ;
	point.y = 0;
	while (point.y < map_t->map_h)
	{
		point.x = 0;
		str = ft_strsplit(tmp->content, ' ');
		map_t->map[point.y] = (int16_t*)malloc(sizeof(int16_t) * map_t->map_w);
		while (point.x < map_t->map_w)
		{
			map_t->map[point.y][point.x] = (int16_t)ft_atoi(str[point.x]);
			point.x++;
		}
		tmp = ft_smooth(&tmp);
		ft_split_del(str);
		point.y++;
	}
}

void		init_sprit(t_map *map_t, t_v2i i, t_spr *sprite)
{
	if (map_t->sprit_num >= MAXSPL)
		map_t->map[i.y][i.x] = 0;
	else
	{
		sprite[map_t->sprit_num].p.x = i.y + 0.5;
		sprite[map_t->sprit_num].p.y = i.x + 0.5;
		sprite[map_t->sprit_num].nm_t = map_t->map[i.y][i.x];
		if (sprite[map_t->sprit_num].nm_t == barrel)
			sprite[map_t->sprit_num].hit = 3;
		else
			sprite[map_t->sprit_num].hit = 999;
	}
	map_t->sprit_num++;
}

void		set_player(t_sdl *sdl, t_v2i point)
{
	sdl->player.x = point.y;
	sdl->player.y = point.x;
	sdl->m_t.map[point.y][point.x] = 0;
}

void		ft_fix_map(t_map *map_t, t_spr *sprite, t_sdl *sdl)
{
	t_v2i	i;

	i.y = 0;
	while (i.y < map_t->map_h && !(i.x = 0))
	{
		while (i.x < map_t->map_w)
		{
			if (i.y == 0)
				while (i.x < map_t->map_w - 1)
					map_t->map[i.y][i.x++] = 1;
			if (i.y == (map_t->map_h - 1))
				while (i.x < map_t->map_w - 1)
					map_t->map[i.y][i.x++] = 1;
			if (map_t->map[i.y][i.x] == 25)
				set_player(sdl, i);
			if (!ft_check_texture(map_t->map[i.y][i.x]))
				map_t->map[i.y][i.x] = 0;
			if (i.x == 0 || i.x == map_t->map_w - 1)
				map_t->map[i.y][i.x] = 1;
			if (ft_check_sprite(map_t->map[i.y][i.x]))
				init_sprit(map_t, i, sprite);
			i.x++;
		}
		i.y++;
	}
}

int8_t		ft_make_map(t_sdl *sdl)
{
	int16_t	fd;

	if (!(sdl->argv_t.flag & MAPN))
		return (ft_errors("\nError m_t flag"));
	else
	{
		fd = (int16_t)open(sdl->argv_t.map_name, O_RDONLY);
		if (fd < 1)
			return (ft_errors("\nError fd"));
		else
			sdl->m_t.head = ft_pars_file(fd);
	}
	ft_revers_list(&sdl->m_t.head);
	if (!ft_mapping(&sdl->m_t, sdl->sp, sdl))
		return (0);
	close(fd);
	return (1);
}
