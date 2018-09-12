/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 11:13:12 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/07 11:13:17 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		ft_wall(t_cam *cam, t_ray *ray, int16_t pxl_h)
{
	if (ray->side == 0)
		ray->pwd = (ray->map.x - cam->pos.x + (1 - ray->step.x) / 2)
					/ cam->r_dir.x;
	else
		ray->pwd = (ray->map.y - cam->pos.y + (1 - ray->step.y) / 2)
					/ cam->r_dir.y;
	ray->wall.line_h = (int32_t)(pxl_h / ray->pwd);
	ray->wall.draw_start = -ray->wall.line_h / 2 + pxl_h / 2;
	if (ray->wall.draw_start < 0)
		ray->wall.draw_start = 0;
	ray->wall.draw_end = ray->wall.line_h / 2 + pxl_h / 2;
	if (ray->wall.draw_end >= pxl_h)
		ray->wall.draw_end = pxl_h - 1;
}

uint32_t	ft_d_color(Uint32 in_c, t_ray *ray)
{
	Uint32	out_c;
	int		cof;

	cof = 3;
	ray->wall.clr.r = (uint8_t)((in_c >> 16) & 0xFF);
	ray->wall.clr.g = (uint8_t)((in_c >> 8) & 0xFF);
	ray->wall.clr.b = (uint8_t)((in_c) & 0xFF);
	if (ray->pwd > cof)
	{
		ray->wall.clr.r = (uint8_t)(((in_c & 0xFF0000) >> 16)
								/ (1 + (ray->pwd - cof) / 2));
		ray->wall.clr.g = (uint8_t)(((in_c & 0xFF00) >> 8)
								/ (1 + (ray->pwd - cof) / 2));
		ray->wall.clr.b = (uint8_t)((in_c & 0xFF)
								/ (1 + (ray->pwd - cof) / 2));
	}
	out_c = (ray->wall.clr.r << 16) | (ray->wall.clr.g << 8) | ray->wall.clr.b;
	return (out_c);
}

uint32_t	ft_d_c_wall(Uint32 in_c, int y, t_ray *ray, t_map *m_t)
{
	double	centre;
	double	end;
	double	cof;
	Uint32	out_c;

	ray->wall.clr.r = (uint8_t)((in_c >> 16) & 0xFF);
	ray->wall.clr.g = (uint8_t)((in_c >> 8) & 0xFF);
	ray->wall.clr.b = (uint8_t)((in_c) & 0xFF);
	centre = m_t->pxl_s_h / 2;
	end = m_t->pxl_s_h - (centre * 0.5);
	cof = ((double)y - centre) / end;
	if (y > m_t->pxl_s_h / 2)
	{
		ray->wall.clr.r = (uint8_t)(((in_c & 0xFF0000) >> 16) * (cof));
		ray->wall.clr.g = (uint8_t)(((in_c & 0xFF00) >> 8) * (cof));
		ray->wall.clr.b = (uint8_t)((in_c & 0xFF) * (cof));
	}
	out_c = (ray->wall.clr.r << 16) | (ray->wall.clr.g << 8) | ray->wall.clr.b;
	return (out_c);
}

void		ft_dop_tex_w(t_sdl *sdl_t, t_cam *cam, t_ray *ray)
{
	if (ray->side == 0)
		sdl_t->tex_t.wall_x = cam->pos.y + ray->pwd * cam->r_dir.y;
	else
		sdl_t->tex_t.wall_x = cam->pos.x + ray->pwd * cam->r_dir.x;
	sdl_t->tex_t.wall_x -= floor((sdl_t->tex_t.wall_x));
	sdl_t->tex_t.txy.x = (int)(sdl_t->tex_t.wall_x
						* (double)sdl_t->tex_t.twh.x);
	if (ray->side == 0 && cam->r_dir.x > 0)
		sdl_t->tex_t.txy.x = sdl_t->tex_t.twh.x - sdl_t->tex_t.txy.x - 1;
	if (ray->side == 1 && cam->r_dir.y < 0)
		sdl_t->tex_t.txy.x = sdl_t->tex_t.twh.x - sdl_t->tex_t.txy.x - 1;
}

void		ft_draw_tex_w(t_sdl *sdl_t, t_cam *cam, t_ray *ray, uint16_t x)
{
	int32_t		y;
	uint32_t	color;

	ft_dop_tex_w(sdl_t, cam, ray);
	sdl_t->z_buff[x] = ray->pwd;
	y = ray->wall.draw_start;
	while (y < ray->wall.draw_end)
	{
		if (ft_check_sprite(ray->texture))
			return ;
		sdl_t->tex_t.d = y * 256 - sdl_t->m_t.pxl_s_h
							* 128 + ray->wall.line_h * 128;
		sdl_t->tex_t.txy.y = ((sdl_t->tex_t.d * sdl_t->tex_t.twh.x)
							/ ray->wall.line_h) / 256;
		sdl_t->tex_t.pxl = (uint32_t*)sdl_t->txtr[ray->texture]->pixels;
		color = (uint32_t)sdl_t->tex_t.pxl[(sdl_t->tex_t.twh.y
							* sdl_t->tex_t.txy.y + sdl_t->tex_t.txy.x)];
		color = ft_d_color(color, ray);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		sdl_t->tex_t.pxl2[sdl_t->m_t.pxl_s_w * y + x] = color;
		y++;
	}
}
