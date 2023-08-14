/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:48:00 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/14 15:16:21 by htalhaou         ###   ########.fr       */
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
	while ((*next).x >= 0 && (*next).x <= g_game->img_map->width \
		&& (*next).y >= 0 && (*next).y <= g_game->img_map->height)
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

t_ray	get_ray(float ray_angle)
{
	t_ray	h_ray;
	t_ray	v_ray;
	float	fish_eye_fix;

	h_ray = horizontal_ray_intersection(ray_angle);
	v_ray = vertical_ray_intersection(ray_angle);
	if (h_ray.was_hit)
		h_ray.distance = distance_between_points(g_game->player.x, \
			g_game->player.y, h_ray.wall_hit_x, h_ray.wall_hit_y);
	else
		h_ray.distance = INT_MAX;
	if (v_ray.was_hit)
		v_ray.distance = distance_between_points(g_game->player.x, \
			g_game->player.y, v_ray.wall_hit_x, v_ray.wall_hit_y);
	else
		v_ray.distance = INT_MAX;
	fish_eye_fix = cos(ray_angle - g_game->player.angle);
	h_ray.wall_height = (HEIGHT / (h_ray.distance * fish_eye_fix / TILE_SIZE));
	v_ray.wall_height = (HEIGHT / (v_ray.distance * fish_eye_fix / TILE_SIZE));
	if (h_ray.distance < v_ray.distance)
		return ((v_ray.was_hit_vert = 0), h_ray);
	else
		return ((v_ray.was_hit_vert = 1), v_ray);
}
