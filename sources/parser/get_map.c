/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:06 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/02 20:05:29 by yelaissa         ###   ########.fr       */
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
		map = ft_strjoin(map, line);
		free(line);
	}
	return (map);
}

char	**get_map(char *file)
{
	int		fd;
	char	*map_str;
	char	**map;

	map = NULL;
	if (!check_file(file, &fd))
		return (0);
	map_str = read_map(fd);
	if (!map_str)
		return (0);
	map = ft_split(map_str, "\n");
	free(map_str);
	close(fd);
	return (map);
}
