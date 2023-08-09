/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:58:12 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/09 10:08:48 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	save_player_info(int i, int j, char dir)
{
	g_game->player.x = j * TILE_SIZE ;
	g_game->player.y = i * TILE_SIZE ;
	g_game->player.dir = dir;
	if (dir == 'N')
		g_game->player.angle = 1.5 * M_PI;
	else if (dir == 'S')
		g_game->player.angle = 0.5 * M_PI;
	else if (dir == 'E')
		g_game->player.angle = 0;
	else
		g_game->player.angle = M_PI;
}

int	count_cols(char **map)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (map[i])
	{
		if ((int) ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

int	is_valid_elements(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("01WNSE ", map[i][j]) == NULL)
				return (0);
			if (ft_strchr("WNSE", map[i][j]))
				save_player_info(i, j, map[i][j]);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_one_wnse(char **map)
{
	int		wnse_count;
	int		i;
	int		j;

	wnse_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'W' || map[i][j] == 'N' \
				|| map[i][j] == 'S' || map[i][j] == 'E')
				wnse_count++;
			j++;
		}
		i++;
	}
	return (wnse_count == 1);
}

int is_surrounded(char **map)
{
	int i, j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' \
					|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
