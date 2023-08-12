/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:06 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/12 22:13:14 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char *file, int *fd)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot || dot == file)
		return (0);
	if (ft_strncmp("cub", dot + 1, 3) == 0 && ft_strlen(dot) == 4)
	{
		*fd = open(file, O_RDONLY);
		if (*fd == -1)
		{
			throw_err(strerror(errno));
			close(*fd);
			return (0);
		}
	}
	else
	{
		throw_err(ERR_CUB);
		return (0);
	}
	return (1);
}

char	*read_map(int fd)
{
	char	*line;
	char	*map;
	char	*tmp;
	int		map_start;
	int		map_end;

	map_start = -1;
	map_end = -1;
	line = get_next_line(fd);
	if (!line)
		return (throw_err("Invalid map file."), (void *)0);
	map = line;
	int i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_strjoin_gnl(map, line);
		tmp = ft_strtrim(line, "\n");
		if (is_all_wall(tmp) && map_start != -1)
			map_end = i;
		if (is_all_wall(tmp) && map_start == -1)
			map_start = i;
		if (map_start != -1 && map_end == -1 && (ft_strlen(ft_strtrim(line, " \n")) == 0 || line[0] == '\n'))
			return (throw_err("Newline inside the map."), (void *)0);
		free(tmp);
		free(line);
		i++;
	}
	close(fd);
	return (map);
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

t_map	*get_map(char *file)
{
	int		fd;
	char	*map_str;
	char	**map_arr;
	t_map	*map;

	map_arr = NULL;
	if (!check_file(file, &fd))
		return (0);
	map_str = read_map(fd);
	if (!map_str)
		return (0);
	map_arr = ft_split(map_str, "\n");
	free(map_str);
	map = check_map(map_arr);
	free_arr(map_arr);
	if (!map)
		exit(1);
	return (map);
}
