/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:10:41 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/14 15:27:12 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delta_utils_vert(t_cords *delta, t_cords *step, \
	t_ray ray, float ray_angle)
{
	(*delta).x = (int)(g_game->player.x / TILE_SIZE) * TILE_SIZE;
	if (ray.is_right)
		(*delta).x += TILE_SIZE;
	(*delta).y = g_game->player.y + \
		((*delta).x - g_game->player.x) * tan(ray_angle);
	(*step).x = TILE_SIZE;
	if (ray.is_left)
		(*step).x *= -1;
	(*step).y = TILE_SIZE * tan(ray_angle);
	if (ray.is_up && (*step).y > 0)
		(*step).y *= -1;
	if (ray.is_down && (*step).y < 0)
		(*step).y *= -1;
}

void	check_utils_vertical(t_cords *check, \
	t_cords *next, t_ray *ray, t_cords *step)
{
	while ((*next).x >= 0 && (*next).x <= g_game->img_map->width \
		&& (*next).y >= 0 && (*next).y <= g_game->img_map->height)
	{
		if ((*ray).is_left)
			(*check).x = (*next).x - 1;
		else
			(*check).x = (*next).x;
		(*check).y = (*next).y;
		if (check_wall((*check).x, (*check).y))
		{
			(*ray).was_hit = 1;
			(*ray).wall_hit_x = (*next).x;
			(*ray).wall_hit_y = (*next).y;
			break ;
		}
		else
		{
			(*next).x += (*step).x;
			(*next).y += (*step).y;
		}
	}
}

t_ray	vertical_ray_intersection(float ray_angle)
{
	t_cords		delta;
	t_cords		step;
	t_cords		next;
	t_cords		check;
	t_ray		ray;

	ru_first_check(&ray, ray_angle);
	delta_utils_vert(&delta, &step, ray, ray_angle);
	next.x = delta.x;
	next.y = delta.y;
	check_utils_vertical(&check, &next, &ray, &step);
	return (ray);
}
