/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:46:29 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:46:29 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		ft_set_cam(t_cam *cam, t_v2i player)
{
	cam->pos.x = player.x + 0.5;
	cam->pos.y = player.y + 0.5;
	if (player.x <= 0 || player.y <= 0)
	{
		cam->pos.x = 7.5;
		cam->pos.y = 1.5;
	}
	cam->dir.x = -1;
	cam->dir.y = 0;
	cam->pl.x = 0;
	cam->pl.y = 0.66;
}

void		ft_set_time(t_time *t)
{
	t->old_time = t->time;
	t->time = SDL_GetTicks();
	t->frame_time = (t->time - t->old_time) / 1000.0;
	t->m_sp = t->frame_time * 3.0;
	if (t->m_sp > 0.15)
		t->m_sp = 0.15;
	t->rot_s = t->frame_time * 2.5;
}

void		ft_set_pix_for(SDL_PixelFormat *p_format)
{
	p_format->BitsPerPixel = 32;
	p_format->BytesPerPixel = 4;
	p_format->palette = NULL;
	p_format->Rmask = 0;
	p_format->Gmask = 0;
	p_format->Bmask = 0;
	p_format->Amask = 0;
}

void		ft_set_music(t_sdl *sdl_t)
{
	sdl_t->num_track = 0;
	sdl_t->music[0] = Mix_LoadMUS("sound/Future_City_Funk.mp3");
	sdl_t->music[1] = Mix_LoadMUS("sound/Itty_Bitty_8_Bit.mp3");
	sdl_t->volume = 20;
	if (!sdl_t->music[0])
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
	else
		Mix_PlayMusic(sdl_t->music[sdl_t->num_track], -1);
	Mix_VolumeMusic(sdl_t->volume);
}

SDL_Color	ft_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
	SDL_Color color;

	color.a = 0;
	color.r = red;
	color.g = green;
	color.b = blue;
	return (color);
}
