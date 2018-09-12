/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:44:38 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 10:44:39 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int8_t	ft_init_sdl(t_sdl *sdl_t)
{
	int8_t	result;

	result = 1;
	sdl_t->m_t.pxl_s_w = (sdl_t->argv_t.flag & MAPW) ?
							sdl_t->argv_t.screen_w : (int16_t)DEF_SCREEN_WIDTH;
	sdl_t->m_t.pxl_s_h = (sdl_t->argv_t.flag & MAPH) ?
							sdl_t->argv_t.screen_h : (int16_t)DEF_SCREEN_HEIGHT;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 && result--)
		ft_putendl_fd(SDL_GetError(), 2);
	else
	{
		sdl_t->window = SDL_CreateWindow("Doom style", 960, 400,
			sdl_t->m_t.pxl_s_w, sdl_t->m_t.pxl_s_h, SDL_WINDOW_SHOWN);
		if (!sdl_t->window && result--)
			ft_putendl_fd(SDL_GetError(), 2);
		else
		{
			sdl_t->ren = SDL_CreateRenderer(sdl_t->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			sdl_t->txtr = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * TEXTURS);
		}
	}
	return (result);
}

int8_t	ft_init_mix(void)
{
	int8_t	result;
	int		initted;

	result = 1;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 && result--)
		printf("SDL_mixer Error: %s\n", Mix_GetError());
	initted = Mix_Init(MIX_INIT_MP3);
	if ((initted & MIX_INIT_MP3) != MIX_INIT_MP3 && result--)
		printf("SDL_mixer Error: %s\n", Mix_GetError());
	return (result);
}

int8_t	ft_init_ttf(t_sdl *sdl_t)
{
	int8_t	result;

	result = 1;
	if (TTF_Init() == -1 && result--)
		printf("TTF_Init: %s\n", TTF_GetError());
	else
	{
		sdl_t->g_font = TTF_OpenFont("font/wolfenstein.ttf", 28);
		if (sdl_t->g_font == NULL && result--)
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	return (result);
}

int8_t	ft_init_img(void)
{
	int8_t	result;
	int		img_flags;

	result = 1;
	img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags) && result--)
		ft_errors("IMG Init error!");
	return (result);
}

int8_t	ft_init(t_sdl *sdl_t)
{
	int8_t	result;

	result = 0;
	if (ft_init_sdl(sdl_t) > 0 && ++result)
		if (ft_init_ttf(sdl_t) > 0 && ++result)
			if (ft_init_mix() > 0 && ++result)
				if (ft_init_img() > 0 && ++result)
					sdl_t->flag = MENU;
	if (result != 4)
		result = 0;
	sdl_t->loop = 1;
	sdl_t->menu_f = 0;
	sdl_t->m_t.sprit_num = 0;
	sdl_t->player.x = 0;
	sdl_t->player.y = 0;
	return (result);
}
