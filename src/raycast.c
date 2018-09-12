/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:44:19 by istalevs          #+#    #+#             */
/*   Updated: 2018/09/08 11:44:19 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	ft_init_ray(t_sdl *sdl_t, t_cam *cam, t_ray *ray, uint16_t x)
{
	cam->cam_x = 2 * x / (double)sdl_t->m_t.pxl_s_w - 1;
	cam->r_dir.x = cam->dir.x + cam->pl.x * cam->cam_x;
	cam->r_dir.y = cam->dir.y + cam->pl.y * cam->cam_x;
	ray->map.x = (int32_t)cam->pos.x;
	ray->map.y = (int32_t)cam->pos.y;
	ray->hit = 0;
	ray->side = 0;
	ray->delt_d.x = fabs(1 / cam->r_dir.x);
	ray->delt_d.y = fabs(1 / cam->r_dir.y);
}

void	ft_ray(t_cam *cam, t_ray *ray)
{
	if (cam->r_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_d.x = (cam->pos.x - ray->map.x) * ray->delt_d.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_d.x = (ray->map.x + 1.0 - cam->pos.x) * ray->delt_d.x;
	}
	if (cam->r_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_d.y = (cam->pos.y - ray->map.y) * ray->delt_d.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_d.y = (ray->map.y + 1.0 - cam->pos.y) * ray->delt_d.y;
	}
}

void	ft_cast(t_ray *ray, t_map *map_t)
{
	while (ray->hit == 0)
	{
		if (ray->side_d.x < ray->side_d.y)
		{
			ray->side_d.x += ray->delt_d.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_d.y += ray->delt_d.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map_t->map[ray->map.x][ray->map.y] > 0
		&& map_t->map[ray->map.x][ray->map.y] < barrel)
			ray->hit = 1;
	}
	ray->texture = map_t->map[ray->map.x][ray->map.y];
}
