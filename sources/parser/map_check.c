/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusufisawi <yusufisawi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:58:12 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/04 15:08:22 by yusufisawi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			{
				g_game->player.x = j;
				g_game->player.y = i;
				g_game->player.dir = map[i][j];
			}
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

int	valid_map(char **map, int *cols, int *rows)
{
	*cols = count_cols(map);
	*rows = ft_arrlen(map);

	if (!is_valid_elements(map))
		return (throw_err(ERR_ELEMS), 0);
	if (!is_one_wnse(map))
		return (throw_err(ERR_PLAYERS), 0);
	if (!is_surrounded(map))
		return (throw_err(ERR_WALL), 0);
	return (1);
}

t_map	*check_map(char **map)
{
	t_map	*_map;

	_map = (t_map *) malloc(sizeof(t_map));
	if (!_map)
		return (NULL);
	_map->info = check_infos(map);
	if (!_map->info || (_map->info && !valid_info(&(_map->info))))
		return (NULL);
	_map->map = ft_arrdup(map + _map->info->last);
	if (!valid_map(_map->map, &_map->width, &_map->height))
		return (free_map(_map), NULL);
	return (_map);
}

