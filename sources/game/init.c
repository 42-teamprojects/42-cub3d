/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:40:58 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/16 08:30:29 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_assets(void)
{
	g_game->no = mlx_load_png("./assets/north.png");
	if (!g_game->no)
		return (1);
	g_game->we = mlx_load_png("./assets/west.png");
	if (!g_game->we)
		return (mlx_delete_texture(g_game->no), 1);
	g_game->ea = mlx_load_png("./assets/east.png");
	if (!g_game->ea)
		return (mlx_delete_texture(g_game->no), \
			mlx_delete_texture(g_game->we), 1);
	g_game->so = mlx_load_png("./assets/south.png");
	if (!g_game->so)
		return (mlx_delete_texture(g_game->no), \
			mlx_delete_texture(g_game->ea), \
			mlx_delete_texture(g_game->we), 1);
	return (0);
}

int	*parse_pixels(int width, int height, unsigned char *data)
{
	int	*img_colors;
	int	i;
	int	j;

	img_colors = (int *)malloc(sizeof(int) * (width * height));
	if (!img_colors)
		return (NULL);
	i = 0;
	j = 0;
	while (i < height * width * 4)
	{
		img_colors[j] = get_rgba(data[i], data[i + 1], data[i + 2], 1);
		j++;
		i += 4;
	}
	return (img_colors);
}

int	save_pixels(void)
{
	g_game->no_pxls = parse_pixels(g_game->no->width, \
		g_game->no->height, g_game->no->pixels);
	if (!g_game->no_pxls)
		return (1);
	g_game->we_pxls = parse_pixels(g_game->we->width, \
		g_game->we->height, g_game->we->pixels);
	if (!g_game->we_pxls)
		return (free(g_game->no_pxls), 1);
	g_game->ea_pxls = parse_pixels(g_game->ea->width, \
		g_game->ea->height, g_game->ea->pixels);
	if (!g_game->ea_pxls)
		return (free(g_game->no_pxls), \
			free(g_game->we_pxls), 1);
	g_game->so_pxls = parse_pixels(g_game->so->width, \
		g_game->so->height, g_game->so->pixels);
	if (!g_game->so_pxls)
		return (free(g_game->no_pxls), \
			free(g_game->we_pxls), \
			free(g_game->ea_pxls), 1);
	return (0);
}

int	init_game(char *file)
{
	g_game = (t_game *) malloc(sizeof(t_game));
	if (!g_game)
		return (1);
	g_game->map = parser(file);
	if (!g_game->map)
		return (1);
	g_game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!g_game->mlx)
		return (1);
	if (init_assets())
		return (1);
	if (save_pixels())
		return (1);
	g_game->img_map = mlx_new_image(g_game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(g_game->mlx, g_game->img_map, 0, 0);
	mlx_loop_hook(g_game->mlx, ft_hook, g_game);
	return (0);
}
