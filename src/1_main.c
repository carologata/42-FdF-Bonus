#include "../include/fdf.h"

int32_t	main(int32_t argc, char *argv[])
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*mlx_image;

	check_args(argc, argv[1]);
	mlx = init_mlx();
	if (mlx == NULL)
		error("mlx init failed.");
	mlx_image = init_image(mlx);
	if (mlx_image == NULL)
		error("mlx image init failed.");
	map = init_map(argv[1]);
	map->mlx = mlx;
	map->mlx_image = mlx_image;
	init_position(map);
	randomize(map);
	if (init_window(mlx, mlx_image) == -1)
		error("mlx window init failed.");
	// mlx_loop_hook(mlx, ft_hook_translate, map);
	mlx_loop_hook(mlx, ft_hook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_matrix((void **)map->matrix);
	free(map);
	return (EXIT_SUCCESS);
}
