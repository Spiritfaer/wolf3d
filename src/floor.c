/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:37:00 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 10:37:01 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_floor_cast(t_ray *ray, t_tex *tex_t, t_cam *cam_t, t_floor *floor_t)
{
	if (ray->side == 0 && cam_t->r_dir.x > 0)
	{
		floor_t->f_wall.x = ray->map.x;
		floor_t->f_wall.y = ray->map.y + tex_t->wall_x;
	}
	else if (ray->side == 0 && cam_t->r_dir.x < 0)
	{
		floor_t->f_wall.x = ray->map.x + 1.0;
		floor_t->f_wall.y = ray->map.y + tex_t->wall_x;
	}
	else if (ray->side == 1 && cam_t->r_dir.y > 0)
	{
		floor_t->f_wall.x = ray->map.x + tex_t->wall_x;
		floor_t->f_wall.y = ray->map.y;
	}
	else
	{
		floor_t->f_wall.x = ray->map.x + tex_t->wall_x;
		floor_t->f_wall.y = ray->map.y + 1.0;
	}
}

void	ft_floor_drawing(t_sdl *sdl_t, t_floor *floor, t_ray *ray, int32_t y)
{
	sdl_t->tex_t.pxl = (uint32_t*)sdl_t->txtr[0]->pixels;
	sdl_t->color = (uint32_t)sdl_t->tex_t.pxl
		[(sdl_t->tex_t.twh.y * floor->f_tex.y + floor->f_tex.x)];
	sdl_t->color = ft_d_c_wall(sdl_t->color, y, ray, &sdl_t->m_t);
	sdl_t->tex_t.pxl2[sdl_t->m_t.pxl_s_w * y + sdl_t->x] = sdl_t->color;
	sdl_t->tex_t.pxl2[(sdl_t->m_t.pxl_s_h - y) * sdl_t->m_t.pxl_s_w
						+ sdl_t->x] = sdl_t->color;
}

void	ft_floor_add(t_floor *floor, t_ray *ray, t_sdl *sdl_t, t_cam *cam_t)
{
	int32_t		y;

	floor->d_wall = ray->pwd;
	if (ray->wall.draw_end < 0)
		ray->wall.draw_end = sdl_t->m_t.pxl_s_h;
	y = ray->wall.draw_end + 1;
	while (y < sdl_t->m_t.pxl_s_h)
	{
		floor->cur_dist = sdl_t->m_t.pxl_s_h / (2.0 * y - sdl_t->m_t.pxl_s_h);
		floor->weight = floor->cur_dist / floor->d_wall;
		floor->f_cur.x = floor->weight * floor->f_wall.x
							+ (1.0 - floor->weight) * cam_t->pos.x;
		floor->f_cur.y = floor->weight * floor->f_wall.y
							+ (1.0 - floor->weight) * cam_t->pos.y;
		floor->f_tex.x = (int)(floor->f_cur.x * sdl_t->tex_t.twh.x)
							% sdl_t->tex_t.twh.x;
		floor->f_tex.y = (int)(floor->f_cur.y * sdl_t->tex_t.twh.y)
							% sdl_t->tex_t.twh.y;
		ft_floor_drawing(sdl_t, floor, ray, y);
		y++;
	}
}
