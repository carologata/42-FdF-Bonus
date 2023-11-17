/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:57:11 by cogata            #+#    #+#             */
/*   Updated: 2023/11/16 13:57:13 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf_bonus.h"

void	check_args(int argc, char *map_name)
{
	int		fd;
	char	*extension;

	if (argc != 2)
		error("ERROR: number of args is invalid.");
	extension = ft_strrchr(map_name, '.');
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		error("ERROR: file is invalid.");
	}
}

mlx_t	*init_mlx(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!mlx)
		return (NULL);
	return (mlx);
}

mlx_image_t	*init_image(mlx_t *mlx)
{
	mlx_image_t	*mlx_image;

	mlx_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx_image)
	{
		mlx_close_window(mlx);
		return (NULL);
	}
	return (mlx_image);
}

int	init_window(mlx_t *mlx, mlx_image_t *mlx_image)
{
	if (mlx_image_to_window(mlx, mlx_image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		return (-1);
	}
	return (0);
}
