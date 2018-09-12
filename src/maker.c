/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:00:04 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:00:06 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Surface	*ft_load_texture(char *name, SDL_PixelFormat *format)
{
	SDL_Surface *opt_sur;
	SDL_Surface *load_sur;

	opt_sur = NULL;
	load_sur = IMG_Load(name);
	if (!load_sur)
		printf("Unload img %s! %s\n", name, IMG_GetError());
	else
	{
		opt_sur = SDL_ConvertSurface(load_sur, format, 0);
		if (!opt_sur)
			printf("Unable to optimize image %s!"
					"SDL Error: %s\n", name, SDL_GetError());
		SDL_FreeSurface(load_sur);
	}
	return (opt_sur);
}

void		ft_make_texture(SDL_Surface **tex, t_tex *tex_t)
{
	int16_t			x;
	SDL_PixelFormat	format;
	static char		*path[TEXTURS] = {"pics/greystone.png",
					"pics/wood.png",
					"pics/eagle.png",
					"pics/purplestone.png",
					"pics/redbrick.png",
					"pics/mossy.png",
					"pics/bluestone.png",
					"pics/colorstone.png",
					"sprite/barrel.png",
					"sprite/greenlight.png",
					"sprite/pillar.png"};

	x = TEXTURS - 1;
	ft_set_pix_for(&format);
	while (x >= 0)
	{
		tex[x] = ft_load_texture(path[x], &format);
		x--;
	}
	tex_t->pxl = NULL;
	tex_t->pxl2 = NULL;
	tex_t->twh.x = 64;
	tex_t->twh.y = 64;
}

void		ft_set_w(t_sdl *sdl_t, TTF_Font *f, SDL_Surface *tmp, char **str)
{
	SDL_Color	black;
	SDL_Color	red;
	int16_t		i;

	black = ft_set_color(0, 0, 0);
	red = ft_set_color(150, 0, 0);
	i = 0;
	while (i < 3)
	{
		tmp = TTF_RenderText_Blended(f, str[i], black);
		TTF_SizeText(f, str[i], &sdl_t->wrds[i].r_q.w, &sdl_t->wrds[i].r_q.h);
		sdl_t->wrds[i].r_q.y = 200 + i * 100;
		sdl_t->wrds[i].r_q.x = (int)((sdl_t->m_t.pxl_s_w / 4) * 2.5);
		sdl_t->wrds[i].bl = SDL_CreateTextureFromSurface(sdl_t->ren, tmp);
		SDL_FreeSurface(tmp);
		tmp = TTF_RenderText_Blended(f, str[i], red);
		sdl_t->wrds[i].red = SDL_CreateTextureFromSurface(sdl_t->ren, tmp);
		SDL_FreeSurface(tmp);
		i++;
	}
}

void		ft_set_hlp(t_sdl *sdl_t, TTF_Font *f, SDL_Surface *tmp, char **str)
{
	SDL_Color	black;
	SDL_Color	red;
	int16_t		i;
	int16_t		k;

	black = ft_set_color(0, 0, 0);
	red = ft_set_color(150, 0, 0);
	i = 4;
	k = 0;
	while (i < 10)
	{
		tmp = TTF_RenderText_Blended(f, str[i], black);
		TTF_SizeText(f, str[i], &sdl_t->wrds[i].r_q.w, &sdl_t->wrds[i].r_q.h);
		sdl_t->wrds[i].r_q.y = sdl_t->wrds[i].r_q.h + k * 100;
		sdl_t->wrds[i].r_q.x = (sdl_t->m_t.pxl_s_w / 2)
								- sdl_t->wrds[i].r_q.w / 2;
		sdl_t->wrds[i].bl = SDL_CreateTextureFromSurface(sdl_t->ren, tmp);
		SDL_FreeSurface(tmp);
		tmp = TTF_RenderText_Blended(f, str[i], red);
		sdl_t->wrds[i].red = SDL_CreateTextureFromSurface(sdl_t->ren, tmp);
		SDL_FreeSurface(tmp);
		i++;
		k++;
	}
}

void		ft_make_text(t_sdl *sdl)
{
	static char	*str[] = {"START GAME", "HELP", "QUIT", "PRESS",
	"P - poused music", "UP, DOWN, LEFT and RIGHT - moving",
	"W, S, A and D - moving", "MIN or PLUS - change music volume",
	"O - change track", "BACK TO MENU"};
	static char	*font = "font/wolfenstein.ttf";
	SDL_Surface *tmp;
	TTF_Font	*g_font;
	TTF_Font	*g_font_big;

	tmp = NULL;
	g_font = TTF_OpenFont(font, sdl->m_t.pxl_s_h / 9);
	g_font_big = TTF_OpenFont(font, sdl->m_t.pxl_s_h / 5);
	ft_set_w(sdl, g_font, tmp, str);
	ft_set_hlp(sdl, g_font, tmp, str);
	tmp = TTF_RenderText_Blended(g_font, "_%", ft_set_color(150, 0, 0));
	TTF_SizeText(g_font_big, "_%",
				&sdl->wrds[3].r_q.w, &sdl->wrds[3].r_q.h);
	sdl->wrds[3].bl = SDL_CreateTextureFromSurface(sdl->ren, tmp);
	sdl->wrds[3].r_q.y = (int)(sdl->m_t.pxl_s_h / 2.5)
						- sdl->wrds[3].r_q.h / 2;
	sdl->wrds[3].r_q.x = (int)(sdl->m_t.pxl_s_w / 3.2)
						- sdl->wrds[3].r_q.w / 2;
	SDL_FreeSurface(tmp);
	TTF_CloseFont(g_font);
	TTF_CloseFont(g_font_big);
}
