/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:48:09 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/20 12:59:10 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ru_first_check(t_ray *ray, float ray_angle)
{
	ray_angle = normalize_angle(ray_angle);
	(*ray).is_down = (ray_angle > 0 && ray_angle < M_PI);
	(*ray).is_up = !(*ray).is_down;
	(*ray).is_right = (ray_angle < (M_PI / 2) || ray_angle > (3 * M_PI) / 2);
	(*ray).is_left = !(*ray).is_right;
	(*ray).was_hit = 0;
	(*ray).wall_hit_x = 0;
	(*ray).wall_hit_y = 0;
}

void	delta_utils(t_cords *delta, t_cords *step, t_ray ray, float ray_angle)
{
	(*delta).y = floor(g_game->player.y / TILE_SIZE) * TILE_SIZE;
	if (ray.is_down)
		(*delta).y += TILE_SIZE;
	(*delta).x = g_game->player.x + \
		((*delta).y - g_game->player.y) / tan(ray_angle);
	(*step).y = TILE_SIZE;
	if (ray.is_up)
		(*step).y *= -1;
	(*step).x = TILE_SIZE / tan(ray_angle);
	if (ray.is_left && (*step).x > 0)
		(*step).x *= -1;
	if (ray.is_right && (*step).x < 0)
		(*step).x *= -1;
}

void	check_utils(t_cords *check, t_cords *next, t_ray *ray, t_cords *step)
{
	while ((*next).x >= 0 && (*next).x <= g_game->img_map->width * TILE_SIZE \
		&& (*next).y >= 0 && (*next).y <= g_game->img_map->height * TILE_SIZE)
	{
		if ((*ray).is_up)
			(*check).y = (*next).y - 1;
		else
			(*check).y = (*next).y;
		(*check).x = (*next).x;
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

t_ray	horizontal_ray_intersection(float ray_angle)
{
	t_cords	delta;
	t_cords	step;
	t_cords	next;
	t_cords	check;
	t_ray	ray;

	ru_first_check(&ray, ray_angle);
	delta_utils(&delta, &step, ray, ray_angle);
	next.x = delta.x;
	next.y = delta.y;
	check_utils(&check, &next, &ray, &step);
	return (ray);
}
