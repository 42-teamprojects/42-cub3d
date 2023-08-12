/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:28:07 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/12 21:08:42 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_all_wall(char *line)
{
	int		i;
	char	*tmp;
	int		count;

	tmp = ft_strtrim(line, " ");
	i = 0;
	count = 0;
	while (tmp[i])
	{
		if (tmp[i] == '1')
			count++;
		if (tmp[i] != '1' && tmp[i] != ' ')
			return (free(tmp), 0);
		i++;
	}
	free(tmp);
	if (count >= 2)
		return (1);
	return (0);
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
