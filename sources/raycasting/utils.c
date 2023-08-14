/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:58:46 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/14 15:42:37 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_game->map->map[i])
	{
		j = 0;
		while (g_game->map->map[i][j])
		{
			if (g_game->map->map[i][j] == '1')
				draw_pixels(&g_game->img_map, j * TILE_SIZE, \
				i * TILE_SIZE, get_rgba(255, 255, 255, 1));
			j++;
		}
		i++;
	}
	draw_player(&g_game->img_map, g_game->player.x, \
	g_game->player.y, get_rgba(255, 0, 0, 1));
}

void	dda(float x_x, float y_y, float x1, float y1)
{
	t_cords	d;
	int		steps;
	t_cords	inc;
	t_cords	p;
	int		i;

	d.x = x1 - x_x;
	d.y = y1 - y_y;
	if ((abs((int)d.x)) > (abs((int)d.y)))
		steps = (abs((int)d.x));
	else
		steps = (abs((int)d.y));
	inc.x = d.x / (float)steps;
	inc.y = d.y / (float)steps;
	p.x = g_game->player.x;
	p.y = g_game->player.y;
	i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(g_game->img_map, p.x, p.y, get_rgba(211, 100, 100, 3));
		p.x += inc.x;
		p.y += inc.y;
		i++;
	}
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
