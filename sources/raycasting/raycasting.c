/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/07 16:22:52 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_ray()
{
	float FOV = 60 * (M_PI / 180);
	int num_rays = g_game->img_map->width * TILE_SIZE;
	float rayAngle = g_game->player.angle - (FOV / 2);
	int i = 0;

	while (i < num_rays)
	{
		rayAngle += FOV / (float)num_rays;
		draw_angle_dda(&g_game->img_map, rayAngle);
		i++;
	}
}
