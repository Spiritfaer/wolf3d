/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 11:48:46 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/07 11:48:47 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_game_s(t_sdl *sdl)
{
	if (sdl->event.type == SDL_KEYDOWN)
	{
		if (sdl->cur_key[SDL_SCANCODE_TAB])
		{
			if (sdl->flag == GAME)
			{
				sdl->menu_f = 0;
				sdl->flag = MENU;
			}
			else
				sdl->flag = GAME;
			SDL_Delay(150);
		}
	}
}

void	ft_game_menu_e(t_sdl *sdl)
{
	if (sdl->event.type == SDL_KEYDOWN)
	{
		SDL_Delay(150);
		if (sdl->cur_key[SDL_SCANCODE_UP])
			sdl->menu_f--;
		if (sdl->cur_key[SDL_SCANCODE_DOWN])
			sdl->menu_f++;
		sdl->menu_f = (sdl->menu_f < 0) ? (short)2 : sdl->menu_f;
		sdl->menu_f = (sdl->menu_f > 2) ? (short)0 : sdl->menu_f;
	}
	if (sdl->cur_key[SDL_SCANCODE_RETURN]
		|| sdl->cur_key[SDL_SCANCODE_KP_ENTER])
	{
		if (sdl->menu_f == 0)
			sdl->flag = GAME;
		else if (sdl->menu_f == 1)
			sdl->flag = HELP;
		else if (sdl->menu_f == 2)
			sdl->loop = false;
		SDL_Delay(150);
	}
}

void	ft_menu_help(t_sdl *sdl_t)
{
	if (sdl_t->cur_key[SDL_SCANCODE_RETURN]
			|| sdl_t->cur_key[SDL_SCANCODE_KP_ENTER])
	{
		sdl_t->flag = MENU;
		SDL_Delay(150);
	}
}

void	ft_event_guard(t_sdl *sdl, t_cam *cam)
{
	ft_game_s(sdl);
	if (sdl->event.type == SDL_QUIT)
		sdl->loop = false;
	if (sdl->cur_key[SDL_SCANCODE_ESCAPE])
		sdl->loop = false;
	if (sdl->cur_key[SDL_SCANCODE_F])
		ft_set_cam(cam, sdl->player);
	ft_shoot_box(sdl, cam);
}

void	event(t_sdl *sdl, t_cam *cam, t_time *time)
{
	if (sdl->flag == GAME)
	{
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		ft_audio_s(sdl);
		ft_audio_v(sdl);
		ft_move(sdl, cam, time);
		ft_rotate(sdl, cam, time);
		if (sdl->cur_key[SDL_SCANCODE_SPACE])
			sdl->weapon.num = 0;
	}
	else if (sdl->flag == MENU)
	{
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		ft_game_menu_e(sdl);
	}
	else if (sdl->flag == HELP)
	{
		SDL_PollEvent(&sdl->event);
		sdl->cur_key = SDL_GetKeyboardState(NULL);
		ft_menu_help(sdl);
	}
	ft_event_guard(sdl, cam);
}
