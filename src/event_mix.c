/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:28:38 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/09 16:28:38 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_audio_v(t_sdl *sdl_t)
{
	if (sdl_t->cur_key[SDL_SCANCODE_KP_PLUS])
	{
		sdl_t->volume += 1;
		if (sdl_t->volume > 100)
			sdl_t->volume = 100;
		Mix_VolumeMusic(sdl_t->volume);
	}
	if (sdl_t->cur_key[SDL_SCANCODE_KP_MINUS])
	{
		sdl_t->volume -= 1;
		if (sdl_t->volume <= 0)
			sdl_t->volume = 0;
		Mix_VolumeMusic(sdl_t->volume);
	}
}

void	ft_audio_s(t_sdl *sdl_t)
{
	if (sdl_t->event.type == SDL_KEYDOWN)
	{
		if (sdl_t->cur_key[SDL_SCANCODE_P])
		{
			if (Mix_PausedMusic() == 1)
				Mix_ResumeMusic();
			else
				Mix_PauseMusic();
		}
		if (sdl_t->cur_key[SDL_SCANCODE_O])
		{
			if (sdl_t->num_track == 1)
				sdl_t->num_track = 0;
			else
				sdl_t->num_track = 1;
			Mix_PlayMusic(sdl_t->music[sdl_t->num_track], -1);
		}
	}
}
