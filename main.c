/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 15:29:30 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/02 17:29:23 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

int main()
{
    mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return(EXIT_FAILURE);
	}
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}