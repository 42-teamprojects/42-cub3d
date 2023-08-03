/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:06 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/03 15:10:57 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_all_wall(char *line)
{
	int		i;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != '1' && tmp[i] != ' ')
			return (free(tmp), 0);
		i++;
	}
	free(tmp);
	return (1);
}

int	found_info(t_info *info)
{
	if (!info->no || !info->so || !info->we || !info->ea \
		|| !info->_f || !info->_c)
	{
		throw_err(ERR_ELEMS);
		return (0);
	}
	return (1);
}

int	find_info(char *line, t_info *info)
{
	char	**tmp;

	tmp = ft_split(line, " ");
	if (!info->no && !ft_strcmp(tmp[0], "NO") && !ft_strncmp(tmp[1], "./", 2))
		info->no = ft_strdup(tmp[1]);
	else if (!info->so && !ft_strcmp(tmp[0], "SO") \
		&& !ft_strncmp(tmp[1], "./", 2))
		info->so = ft_strdup(tmp[1]);
	else if (!info->we && !ft_strcmp(tmp[0], "WE") \
		&& !ft_strncmp(tmp[1], "./", 2))
		info->we = ft_strdup(tmp[1]);
	else if (!info->ea && !ft_strcmp(tmp[0], "EA") \
		&& !ft_strncmp(tmp[1], "./", 2))
		info->ea = ft_strdup(tmp[1]);
	else if (!info->_f && !ft_strcmp(tmp[0], "F") && ft_isdigit(tmp[1][0]))
		info->_f = ft_strdup(tmp[1]);
	else if (!info->_c && !ft_strcmp(tmp[0], "C") && ft_isdigit(tmp[1][0]))
		info->_c = ft_strdup(tmp[1]);
	else
		return (free_arr(tmp), 0);
	free_arr(tmp);
	return (1);
}

t_info	*check_infos(char **map)
{
	t_info	*info;
	int		i;

	info = (t_info *) ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	i = -1;
	while (map[++i] && !is_all_wall(map[i]))
	{
		if (!find_info(map[i], info))
			return (throw_err(ERR_INFO), free(info), NULL);
	}
	if (!found_info(info))
		return (free(info), NULL);
	info->last = i;
	return (info);
}

t_map	*check_map(char **map)
{
	t_map	*_map;

	_map = (t_map *) malloc(sizeof(t_map));
	if (!_map)
		return (NULL);
	_map->info = check_infos(map);
	if (!_map->info)
		return (NULL);
	printf("NO: %s\n", _map->info->no);
	printf("SO: %s\n", _map->info->so);
	printf("WE: %s\n", _map->info->we);
	printf("EA: %s\n", _map->info->ea);
	printf("F: %s\n", _map->info->_f);
	printf("C: %s\n", _map->info->_c);
	return (_map);
}
