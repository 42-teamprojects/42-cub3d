/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:05:26 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/25 15:10:53 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float ray_angle)
{
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	else if (ray_angle > 2 * M_PI)
		ray_angle = ray_angle - (2 * M_PI);
	return (ray_angle);
}

int	check_wall(float x, float y)
{
	int		x1;
	int		y1;
	float	lenx;

	x1 = (int)x / TILE_SIZE;
	y1 = (int)y / TILE_SIZE;
	if (y1 >= g_game->map->height)
		return (1);
	lenx = ft_strlen(g_game->map->map[y1]);
	if (x1 < 0 || x1 >= lenx || y1 < 0 || y1 >= g_game->map->height)
		return (1);
	if (g_game->map->map[y1][x1] == '1')
		return (1);
	return (0);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
