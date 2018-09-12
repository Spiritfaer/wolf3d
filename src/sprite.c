/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 15:46:45 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/09 15:46:46 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

uint32_t	deep_color_spite(uint32_t in_c, double dist)
{
	double	far;
	double	visib;
	double	cof;
	Uint32	out_c;
	t_rgb	clr;

	clr.r = (uint8_t)((in_c >> 16) & 0xFF);
	clr.g = (uint8_t)((in_c >> 8) & 0xFF);
	clr.b = (uint8_t)((in_c) & 0xFF);
	far = 2;
	if (dist > 20)
		dist = 20;
	visib = 25;
	cof = fabs((dist - far) / visib);
	if (dist < visib)
	{
		clr.r = (uint8_t)(((in_c & 0xFF0000) >> 16) * (1 - cof));
		clr.g = (uint8_t)(((in_c & 0xFF00) >> 8) * (1 - cof));
		clr.b = (uint8_t)((in_c & 0xFF) * (1 - cof));
	}
	out_c = (clr.r << 16) | (clr.g << 8) | clr.b;
	return (out_c);
}

void		ft_sort_spline(t_sdl *sdl, t_cam *cam, t_sp *s_calc)
{
	s_calc->i = 0;
	while (s_calc->i < sdl->m_t.sprit_num)
	{
		sdl->sp[s_calc->i].dist = ((cam->pos.x - sdl->sp[s_calc->i].p.x)
			* (cam->pos.x - sdl->sp[s_calc->i].p.x)
			+ (cam->pos.y - sdl->sp[s_calc->i].p.y)
			* (cam->pos.y - sdl->sp[s_calc->i].p.y));
		s_calc->i++;
	}
	if (sdl->m_t.sprit_num > 1)
		ft_sort((void**)sdl->sp, sdl->m_t.sprit_num);
	s_calc->i = 0;
}

void		ft_cacl_sprite(t_sdl *sdl, t_cam *cam, t_sp *sp_t)
{
	sdl->tex_t.pxl3 = sdl->txtr[sdl->sp[sp_t->i].nm_t]->pixels;
	sp_t->sp.x = sdl->sp[sp_t->i].p.x - cam->pos.x;
	sp_t->sp.y = sdl->sp[sp_t->i].p.y - cam->pos.y;
	sp_t->invdet = 1.0 / (cam->pl.x * cam->dir.y - cam->dir.x * cam->pl.y);
	sp_t->trform.x = sp_t->invdet * (cam->dir.y
						* sp_t->sp.x - cam->dir.x * sp_t->sp.y);
	sp_t->trform.y = sp_t->invdet * (-cam->pl.y
						* sp_t->sp.x + cam->pl.x * sp_t->sp.y);
	sp_t->sp_scr_x = (int)((sdl->m_t.pxl_s_w / 2)
						* (1 + sp_t->trform.x / sp_t->trform.y));
	sp_t->sp_h = abs((int)(sdl->m_t.pxl_s_h / sp_t->trform.y));
	sp_t->dr_start.y = (int)(-sp_t->sp_h / 2.0 + sdl->m_t.pxl_s_h / 2.0);
	if (sp_t->dr_start.y < 0)
		sp_t->dr_start.y = 0;
	sp_t->dr_end.y = (int)(sp_t->sp_h / 2.0 + sdl->m_t.pxl_s_h / 2.0);
	if (sp_t->dr_end.y >= sdl->m_t.pxl_s_h)
		sp_t->dr_end.y = sdl->m_t.pxl_s_h - 1;
	sp_t->sp_w = abs((int)(sdl->m_t.pxl_s_h / sp_t->trform.y));
	sp_t->dr_start.x = (int)(-sp_t->sp_w / 2.0 + sp_t->sp_scr_x);
	if (sp_t->dr_start.x < 0)
		sp_t->dr_start.x = 0;
	sp_t->dr_end.x = (int)(sp_t->sp_w / 2.0 + sp_t->sp_scr_x);
	if (sp_t->dr_end.x >= sdl->m_t.pxl_s_w)
		sp_t->dr_end.x = sdl->m_t.pxl_s_w - 1;
}

void		ft_draw_spline(t_sdl *sdl, t_sp *s_calc)
{
	s_calc->y = s_calc->dr_start.y;
	while (s_calc->y < s_calc->dr_end.y)
	{
		s_calc->d = (int)(s_calc->y - sdl->m_t.pxl_s_h
							/ 2.0 + s_calc->sp_h / 2.0);
		s_calc->tex.y = (s_calc->d * sdl->tex_t.twh.y)
							/ s_calc->sp_h;
		s_calc->color = (uint32_t)sdl->tex_t.pxl3[(sdl->tex_t.twh.y
							* s_calc->tex.y + s_calc->tex.x)];
		if ((s_calc->color & 0x00FFFFFF) != 0)
			sdl->tex_t.pxl2[sdl->m_t.pxl_s_w * s_calc->y + s_calc->dr_start.x] =
					deep_color_spite(s_calc->color, sdl->sp[s_calc->i].dist);
		s_calc->y++;
	}
}

void		ft_spline(t_sdl *sdl, t_cam *cam, t_sp *s_calc)
{
	ft_sort_spline(sdl, cam, s_calc);
	while (s_calc->i < sdl->m_t.sprit_num)
	{
		ft_cacl_sprite(sdl, cam, s_calc);
		while (s_calc->dr_start.x <= s_calc->dr_end.x)
		{
			s_calc->tex.x = (int)(256 * (s_calc->dr_start.x
				- (-s_calc->sp_w / 2.0 + s_calc->sp_scr_x))
				* sdl->tex_t.twh.x / s_calc->sp_w) / 256;
			if (s_calc->trform.y > 0 && s_calc->dr_start.x < sdl->m_t.pxl_s_w
				&& s_calc->trform.y < sdl->z_buff[s_calc->dr_start.x])
			{
				ft_draw_spline(sdl, s_calc);
			}
			s_calc->dr_start.x++;
		}
		s_calc->i++;
	}
}
