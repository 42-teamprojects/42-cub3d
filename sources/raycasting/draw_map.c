/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/10 19:58:19 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, float a)
{
    int color;

    color = r << 24 | g << 16 | b << 8 | (int)a * 255;
    return (color);
}

void	draw_pixels(mlx_image_t **img, float h, float w, int color)
{
	float	i;
	float	j;
	(void)color;

	i = h;
	while (i < h + TILE_SIZE)
	{
		j = w;
		while (j < w + TILE_SIZE)
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_pixels3()
{
	float	x;
	float	y;
	
	x = 0;
	while (x < g_game->map->width * TILE_SIZE)
	{
		y = 0;
		while (y < g_game->map->height * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 255, 1));
			y++;
		}
		x += TILE_SIZE;
	}
	x = 0;
	y = 0;
	while (y < g_game->map->height * TILE_SIZE)
	{
		x = 0;
		while (x < g_game->map->width * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 255, 1));
			x++;
		}
		y += TILE_SIZE;
	}
}


void	draw_pixelsv2(mlx_image_t **img, float posx, float posy, int color)
{
	float	i;
	float	j;

	i = posx - 3;
	while (i < (posx +  (TILE_SIZE / 5)) - 3 )
	{
		j = posy - 3;
		while (j < posy +  (TILE_SIZE / 5) - 3 )
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}

}
void	draw_player(mlx_image_t **img, float x, float y)
{
	draw_pixelsv2(img, x, y, 0xFF0000FF);
}

void	draw_map()
{

	int	i;
	int	j;
		i = 0;
	j = 0;
	while(i < g_game->map->width * TILE_SIZE)
	{
		j = 0;
		while(j < g_game->map->height * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, i, j, 0x00000000);
			j++;
		}
		i++;
	} 
	i = 0;
	while (g_game->map->map[i])
	{
		j = 0;
		while (g_game->map->map[i][j])
		{
			if (g_game->map->map[i][j] == '1')
				draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE, get_rgba(255, 255, 255, 1));
			// else if (g_game->map->map[i][j] == '0' || ft_strchr("NSEW", g_game->map->map[i][j]))
			// 		draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE, get_rgba(0, 0, 0, 1));
			j++;
		}
		i++;
	}
	draw_pixels3();
	draw_player(&g_game->img_map, g_game->player.x, g_game->player.y);
}

void DDA(mlx_image_t **img, float X0, float Y0, float X1, float Y1)
{
    int dx = X1 - X0;
    int dy = Y1 - Y0;
	int steps;

	if (abs(dx) > abs(dy))
		steps = abs(dx);		
	else
		steps = abs(dy);
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    float X = g_game->player.x;
    float Y = g_game->player.y;
    for (int i = 0; i <= steps; i++)
    {
        mlx_put_pixel(*img, X, Y, get_rgba(100, 180, 150, 3));
        X += Xinc;
        Y += Yinc;
    }
}

// void draw_angle_dda(mlx_image_t **img, t_cords hits, float ray_angle)
// {
// 	float dx;
// 	float dy;
// 	(void)ray_angle;
// 	float x = g_game->player.x;
//     float y = g_game->player.y;
//     dx = hits.x + cos(ray_angle);
//     dy = hits.y + sin(ray_angle);
//     DDA(img, x, y, dx , dy);
// }

void move_forward(float move_speed)
{
	float var = g_game->player.x + cos(g_game->player.angle) * move_speed;
	float var2 = g_game->player.y + sin(g_game->player.angle) * move_speed;
	if (g_game->map->map[(int)(var2 / TILE_SIZE)][(int)((var / TILE_SIZE))] != '1'
	&& g_game->map->map[(int)(var2 / TILE_SIZE)][(int)(g_game->player.x / TILE_SIZE)] != '1' &&
	g_game->map->map[(int)(g_game->player.y / TILE_SIZE)][(int)(var / TILE_SIZE)] != '1')
	{
		g_game->player.x = var;
		g_game->player.y = var2;
	}
}

void move_backward(float move_speed)
{
	float var = g_game->player.x - cos(g_game->player.angle) * move_speed;
	float var2 = g_game->player.y - sin(g_game->player.angle) * move_speed;
	if (g_game->map->map[(int)(var2 / TILE_SIZE)][(int)((var / TILE_SIZE))] != '1'
	&& g_game->map->map[(int)(var2 / TILE_SIZE)][(int)(g_game->player.x / TILE_SIZE)] != '1' &&
	g_game->map->map[(int)(g_game->player.y / TILE_SIZE)][(int)(var / TILE_SIZE)] != '1')
	{
		g_game->player.x = var;
		g_game->player.y = var2;
	}
}

void move_left(float move_speed)
{
	float var =	g_game->player.x + sin(g_game->player.angle) * move_speed; 
	float var2 = g_game->player.y - cos(g_game->player.angle) * move_speed; 
	if (g_game->map->map[(int)(var2 / TILE_SIZE)][(int)((var / TILE_SIZE))] != '1'
	&& g_game->map->map[(int)(var2 / TILE_SIZE)][(int)(g_game->player.x / TILE_SIZE)] != '1' &&
	g_game->map->map[(int)(g_game->player.y / TILE_SIZE)][(int)(var / TILE_SIZE)] != '1')
	{
		g_game->player.x = var;
		g_game->player.y = var2;
	}

}

void move_right(float move_speed)
{
	float var =	g_game->player.x - sin(g_game->player.angle) * move_speed; 
	float var2 = g_game->player.y + cos(g_game->player.angle) * move_speed; 
	if (g_game->map->map[(int)(var2 / TILE_SIZE)][(int)((var / TILE_SIZE))] != '1'
	&& g_game->map->map[(int)(var2 / TILE_SIZE)][(int)(g_game->player.x / TILE_SIZE)] != '1' &&
	g_game->map->map[(int)(g_game->player.y / TILE_SIZE)][(int)(var / TILE_SIZE)] != '1')
	{
		g_game->player.x = var;
		g_game->player.y = var2;
	}
}

void ft_hook(void* param)
{
	(void)param;
	float move_speed;
	float rot_speed;

	move_speed = 2;
	rot_speed = 0.09;

	if (mlx_is_key_down(g_game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g_game->mlx);
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_W))
		move_forward(move_speed);
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_S))
		move_backward(move_speed);
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_A))
		move_left(move_speed);
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_D))
		move_right(move_speed);
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_LEFT))
		{
			g_game->player.angle -= rot_speed;
			g_game->player.angle = normalize_angle(g_game->player.angle);
		}
	if (mlx_is_key_down(g_game->mlx, MLX_KEY_RIGHT))
		{
			g_game->player.angle += rot_speed;
			g_game->player.angle = normalize_angle(g_game->player.angle);
		}
	draw_map();
	cast_ray();
}
