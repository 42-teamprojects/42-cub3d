/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:07:29 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/02 20:37:43 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "global.h"

t_game	*g_game;

// Parser
t_map	*parser(char *file);
t_map	*get_map(char *file);
t_map	*check_map(char **map);

// Utils
void	throw_err(char *err);

#endif