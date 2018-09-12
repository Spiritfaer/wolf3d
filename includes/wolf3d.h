/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:57:56 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:57:57 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define DEF_SCREEN_WIDTH 1440
# define DEF_SCREEN_HEIGHT 840
# define AR const char**
# define TEXTURS 11
# define MAXSPL 64

# define MAPN 0x000001
# define MAPW 0x000002
# define MAPH 0x000004

# define MENU 0x000001
# define GAME 0x000002
# define HELP 0x000004

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "SDL_ttf.h"

enum	e_textures {greystone, wood, eagle, purplestone, redbrick,
	mossy, bluestone, colorstone, barrel, greenlight, pillar};

typedef struct		s_rgb
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_rgb;

typedef struct		s_wall
{
	int32_t			draw_start;
	int32_t			draw_end;
	t_rgb			clr;
	int32_t			line_h;
}					t_wall;

typedef struct		s_v2d
{
	double			x;
	double			y;
}					t_v2d;

typedef struct		s_v2i
{
	int32_t			x;
	int32_t			y;
}					t_v2i;

typedef struct		s_spr
{
	t_v2d			p;
	int16_t			nm_t;
	double			dist;
	int				hit;
}					t_spr;

typedef struct		s_arg {
	const char		*map_name;
	Uint16			screen_w;
	Uint16			screen_h;
	Uint8			flag;
	int8_t			error;
}					t_arg;

typedef struct		s_map {
	t_list			*head;
	int16_t			**map;
	int16_t			map_w;
	int16_t			map_h;
	int16_t			pxl_s_w;
	int16_t			pxl_s_h;
	int16_t			sprit_num;
}					t_map;

typedef struct		s_time
{
	double			time;
	double			old_time;
	double			frame_time;
	double			m_sp;
	double			rot_s;
}					t_time;

typedef struct		s_cam
{
	double			cam_x;
	t_v2d			r_dir;
	t_v2d			pos;
	t_v2d			dir;
	t_v2d			pl;
	t_v2d			coll;
}					t_cam;

typedef struct		s_ray
{
	t_v2i			map;
	t_v2i			step;
	t_v2d			side_d;
	t_v2d			delt_d;
	int8_t			hit;
	int8_t			side;
	int16_t			texture;
	double			pwd;
	t_wall			wall;
}					t_ray;

typedef struct		s_floor
{
	t_v2d			f_wall;
	t_v2d			f_cur;
	t_v2i			f_tex;
	double			d_wall;
	double			cur_dist;
	double			weight;
}					t_floor;

typedef struct		s_tex
{
	double			wall_x;
	int32_t			d;
	t_v2i			txy;
	t_v2i			twh;
	uint32_t		*pxl;
	uint32_t		*pxl2;
	uint32_t		*pxl3;
}					t_tex;

typedef struct		s_text
{
	SDL_Rect		r_q;
	SDL_Texture		*bl;
	SDL_Texture		*red;
}					t_text;

typedef struct		s_sp
{
	t_v2d			sp;
	t_v2d			trform;
	t_v2i			dr_start;
	t_v2i			dr_end;
	t_v2i			tex;
	double			invdet;
	int				sp_scr_x;
	int				sp_h;
	int				sp_w;
	int				y;
	int				d;
	int				i;
	uint32_t		color;
}					t_sp;

typedef	struct		s_weapon
{
	int8_t			num;
	SDL_Surface		*weap_sur;
	SDL_Texture		*weap_tex;
	SDL_Rect		anim[6];
	SDL_Rect		box_screen;
}					t_weapon;

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*ren;
	SDL_Event		event;
	const uint8_t	*cur_key;
	SDL_Surface		**txtr;
	t_tex			tex_t;
	int8_t			loop;
	t_arg			argv_t;
	t_map			m_t;
	Uint16			num_track;
	Mix_Music		*music[2];
	int16_t			volume;
	SDL_Surface		*buffer;
	SDL_Texture		*pre_ren;
	uint16_t		x;
	uint32_t		color;
	int32_t			flag;
	TTF_Font		*g_font;
	t_text			wrds[10];
	int16_t			menu_f;
	t_spr			sp[MAXSPL];
	double			z_buff[2048];
	t_sp			s_calc;
	t_weapon		weapon;
	t_v2i			player;
}					t_sdl;

int8_t				ft_read_argv(int argc, AR argv, t_arg *arg);
int8_t				ft_init(t_sdl *sdl_t);
int8_t				ft_make_map(t_sdl *sdl);
int8_t				ft_errors(const char *error);
void				ft_revers_list(t_list **head);
uint_fast32_t		ft_count_list(t_list *head);
int8_t				ft_check_w_map(t_list *head, int16_t map_w);
void				ft_list_del(t_list **head);
void				ft_remap(t_map *map_t);
void				ft_fix_map(t_map *map_t, t_spr *sprite, t_sdl *sdl);
void				ft_split_del(char **head);
void				ft_process(t_sdl *sdl);
void				ft_ray(t_cam *cam, t_ray *ray);
void				ft_cast(t_ray *ray, t_map *map_t);
void				ft_wall(t_cam *cam, t_ray *ray, int16_t pxl_h);
void				ft_set_cam(t_cam *cam, t_v2i player);
void				ft_set_time(t_time *t);
void				event(t_sdl *sdl, t_cam *cam, t_time *time);
void				ft_end(t_sdl *sdl_t);
void				ft_draw_tex_w(t_sdl *sdl_t, t_cam *cam,
									t_ray *ray, uint16_t x);
void				ft_init_ray(t_sdl *sdl_t, t_cam *cam,
									t_ray *ray, uint16_t x);
uint32_t			ft_d_color(Uint32 in_c, t_ray *ray);
uint32_t			ft_d_c_wall(Uint32 in_c, int y, t_ray *ray, t_map *m_t);
void				ft_floor_cast(t_ray *ray, t_tex *tex_t,
									t_cam *cam_t, t_floor *floor_t);
void				ft_floor_add(t_floor *floor, t_ray *ray,
									t_sdl *sdl_t, t_cam *cam_t);
void				ft_set_pix_for(SDL_PixelFormat *p_format);
void				ft_set_music(t_sdl *sdl_t);
void				ft_make_texture(SDL_Surface **tex, t_tex *tex_t);
void				ft_make_text(t_sdl *sdl_t);
t_list				*ft_pars_file(int16_t fd);
int8_t				ft_mapping(t_map *map_t, t_spr *sprite, t_sdl *sdl);
void				ft_move(t_sdl *sdl, t_cam *cam, t_time *t);
void				ft_rotate(t_sdl *sdl_t, t_cam *cam, t_time *t);
void				ft_audio_v(t_sdl *sdl_t);
SDL_Color			ft_set_color(uint8_t red, uint8_t green, uint8_t blue);
void				ft_flag_argv(int i, AR argv, t_arg *arg);
t_list				*ft_smooth(t_list **head);
int8_t				ft_check_sprite(int16_t wall);
void				ft_sort(void **sorted, int16_t size);
void				ft_spline(t_sdl *sdl, t_cam *cam, t_sp *s_calc);
void				ft_audio_s(t_sdl *sdl_t);
int8_t				ft_check_texture(int16_t wall);
SDL_Surface			*ft_load_texture(char *name, SDL_PixelFormat *format);
void				ft_draw_weapon(t_sdl *sdl);
SDL_Color			get_color(uint32_t in_c);
void				ft_shoot_box(t_sdl *sdl, t_cam *cam);
void				ft_make_weapon(t_sdl *sdl, t_weapon *w);
#endif
