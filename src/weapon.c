/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:57:24 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/10 21:57:25 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_set_weapon(t_sdl *sdl, t_weapon *w)
{
	int16_t			x;

	x = 0;
	w->anim[5].x = 0;
	w->anim[5].y = 0;
	w->box_screen.w = w->anim[5].w + 250;
	w->box_screen.h = w->anim[5].h + 250;
	w->box_screen.x = sdl->m_t.pxl_s_h / 2 + w->anim[5].w / 2;
	w->box_screen.y = sdl->m_t.pxl_s_h - w->box_screen.h;
	while (x < 5)
	{
		w->anim[x].w = w->anim[5].w / 5;
		w->anim[x].h = w->anim[5].h / 5;
		w->anim[x].x = 0 + w->anim[5].w / 5 * x + x;
		w->anim[x].y = 5;
		x++;
	}
	sdl->weapon.num = -1;
}

void	ft_make_weapon(t_sdl *sdl, t_weapon *w)
{
	static char		*path = "dopPNG/weapon.png";
	SDL_PixelFormat	format;
	Uint32			form;
	uint32_t		*pixel;
	SDL_Color		col;

	ft_set_pix_for(&format);
	w->weap_sur = ft_load_texture(path, &format);
	pixel = (uint32_t*)(w->weap_sur->pixels);
	col = get_color(pixel[0]);
	SDL_SetColorKey(w->weap_sur, SDL_TRUE,
					SDL_MapRGB(w->weap_sur->format, col.r, col.g, col.b));
	w->weap_tex = SDL_CreateTextureFromSurface(sdl->ren, w->weap_sur);
	SDL_QueryTexture(w->weap_tex, &form, 0, &w->anim[5].w, &w->anim[5].h);
	ft_set_weapon(sdl, w);
}

void	ft_draw_weapon(t_sdl *sdl)
{
	if (sdl->weapon.num == -1)
		SDL_RenderCopy(sdl->ren, sdl->weapon.weap_tex,
			&sdl->weapon.anim[1], &sdl->weapon.box_screen);
	else
	{
		SDL_RenderCopy(sdl->ren, sdl->weapon.weap_tex,
			&sdl->weapon.anim[sdl->weapon.num], &sdl->weapon.box_screen);
		sdl->weapon.num++;
		if (sdl->weapon.num >= 5)
			sdl->weapon.num = -1;
	}
}
