/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:36:04 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 10:36:10 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_shoot_box(t_sdl *sdl, t_cam *cam)
{
	double	k;

	if (sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].dist < 1)
	{
		if (sdl->cur_key[SDL_SCANCODE_SPACE])
		{
			sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].hit--;
			if (sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].hit < 0)
			{
				sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].p.x = -1;
				sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].p.y = -1;
			}
			else if (sdl->sp[(int8_t)(sdl->m_t.sprit_num - 1)].nm_t == barrel)
			{
				if (sdl->cur_key[SDL_SCANCODE_UP]
					|| sdl->cur_key[SDL_SCANCODE_W])
					k = 0.2;
				else
					k = 0.02;
				cam->pos.x -= cam->dir.x * k;
				cam->pos.y -= cam->dir.y * k;
			}
		}
	}
}

t_v2d	ft_cof(t_cam *cam, double vel)
{
	t_v2d box;

	if (cam->dir.x < 0)
		box.x = -vel;
	else
		box.x = vel;
	if (cam->dir.y < 0)
		box.y = -vel;
	else
		box.y = vel;
	return (box);
}

bool	ft_sp_cll(t_sdl *sdl, t_cam *cam, t_time *t, int16_t map)
{
	t_v2d	box;
	double	x;

	x = 4;
	if ((map > greystone && map < barrel))
		return (false);
	if ((map == barrel || map == pillar)
		&& sdl->sp[sdl->m_t.sprit_num - 1].dist < 0.1)
	{
		box = ft_cof(cam, x);
		if (sdl->cur_key[SDL_SCANCODE_UP] || sdl->cur_key[SDL_SCANCODE_W])
		{
			cam->pos.x += (cam->dir.x * t->m_sp) / box.x;
			cam->pos.y += (cam->dir.y * t->m_sp) / box.y;
		}
		return (false);
	}
	return (true);
}

void	ft_move(t_sdl *sdl, t_cam *cam, t_time *t)
{
	t_v2d	wall_box;
	double	x;

	x = 0.1;
	wall_box = ft_cof(cam, x);
	if (sdl->cur_key[SDL_SCANCODE_UP] || sdl->cur_key[SDL_SCANCODE_W])
	{
		if (ft_sp_cll(sdl, cam, t, sdl->m_t.map[(int)(cam->pos.x + cam->dir.x
		* t->m_sp + wall_box.x)][(int)(cam->pos.y + wall_box.y)]) == true)
			cam->pos.x += cam->dir.x * t->m_sp;
		if (ft_sp_cll(sdl, cam, t, sdl->m_t.map[(int)(cam->pos.x + wall_box.x)]
		[(int)(cam->pos.y + cam->dir.y * t->m_sp + wall_box.y)]) == true)
			cam->pos.y += cam->dir.y * t->m_sp;
	}
	if (sdl->cur_key[SDL_SCANCODE_DOWN] || sdl->cur_key[SDL_SCANCODE_S])
	{
		if (ft_sp_cll(sdl, cam, t, sdl->m_t.map[(int)(cam->pos.x - cam->dir.x
		* t->m_sp - wall_box.x)][(int)(cam->pos.y - wall_box.y)]) == true)
			cam->pos.x -= cam->dir.x * t->m_sp;
		if (ft_sp_cll(sdl, cam, t, sdl->m_t.map[(int)(cam->pos.x - wall_box.x)]
		[(int)(cam->pos.y - cam->dir.y * t->m_sp - wall_box.y)]) == true)
			cam->pos.y -= cam->dir.y * t->m_sp;
	}
}

void	ft_rotate(t_sdl *sdl_t, t_cam *cam, t_time *t)
{
	double o_d_x;
	double o_p_x;

	if (sdl_t->cur_key[SDL_SCANCODE_RIGHT] || sdl_t->cur_key[SDL_SCANCODE_D])
	{
		o_d_x = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(-t->rot_s) - cam->dir.y * sin(-t->rot_s);
		cam->dir.y = o_d_x * sin(-t->rot_s) + cam->dir.y * cos(-t->rot_s);
		o_p_x = cam->pl.x;
		cam->pl.x = cam->pl.x * cos(-t->rot_s) - cam->pl.y * sin(-t->rot_s);
		cam->pl.y = o_p_x * sin(-t->rot_s) + cam->pl.y * cos(-t->rot_s);
	}
	if (sdl_t->cur_key[SDL_SCANCODE_LEFT] || sdl_t->cur_key[SDL_SCANCODE_A])
	{
		o_d_x = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(t->rot_s) - cam->dir.y * sin(t->rot_s);
		cam->dir.y = o_d_x * sin(t->rot_s) + cam->dir.y * cos(t->rot_s);
		o_p_x = cam->pl.x;
		cam->pl.x = cam->pl.x * cos(t->rot_s) - cam->pl.y * sin(t->rot_s);
		cam->pl.y = o_p_x * sin(t->rot_s) + cam->pl.y * cos(t->rot_s);
	}
}
