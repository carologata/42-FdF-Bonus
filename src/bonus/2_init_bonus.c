#include "../../include/fdf.h"

void	check_args(int argc, char *map_name)
{
	char	*extension;

	if (argc != 2)
		error("number of args is invalid.");
	extension = ft_strrchr(map_name, '.');
	if (ft_strncmp(extension, ".fdf", 4) != 0)
		error("argument extension is invalid.");
}

mlx_t	*init_mlx(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "FdF", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (NULL);
	}
	return (mlx);
}

mlx_image_t	*init_image(mlx_t *mlx)
{
	mlx_image_t	*mlx_image;

	if (!(mlx_image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (NULL);
	}
	return (mlx_image);
}

int	init_window(mlx_t *mlx, mlx_image_t *mlx_image)
{
	if (mlx_image_to_window(mlx, mlx_image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (-1);
	}
	return (0);
}
