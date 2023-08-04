/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:06 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 14:32:32 by yelaissa         ###   ########.fr       */
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

	line = get_next_line(fd);
	if (!line)
	{
		throw_err("Invalid map file.");
		return (0);
	}
	map = line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map = ft_strjoin_gnl(map, line);
		free(line);
	}
	close(fd);
	return (map);
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