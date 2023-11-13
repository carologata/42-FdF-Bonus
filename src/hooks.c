#include "../include/fdf.h"

void	ft_hook(void *param)
{
	t_map	*map;

	map = param;

	//ESC - Close
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);

	//Translate
	if (mlx_is_key_down(map->mlx, MLX_KEY_UP))
		map->position.y_offset += 5;
	if (mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
		map->position.y_offset -= 5;
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
		map->position.x_offset += 5;
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
		map->position.x_offset -= 5;
	
	//Zoom
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_ADD))
		map->position.scale *= 1.05;
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_SUBTRACT))
		map->position.scale /= 1.05;

	//Rotate in x
	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
		map->position.x_angle += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
		map->position.x_angle -= 1;
	
	//Rotate in y
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
		map->position.y_angle += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_X))
		map->position.y_angle -= 1;

	//Rotate in z
	if (mlx_is_key_down(map->mlx, MLX_KEY_J))
		map->position.z_angle += 1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_K))
		map->position.z_angle -= 1;

	//Views
	if (mlx_is_key_down(map->mlx, MLX_KEY_I))
	{
		map->position.x_angle = 54;
		map->position.y_angle = 0;
		map->position.z_angle = -45;
		map->position.isometric_angle = 0;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_O))
	{
		map->position.x_angle = 0;
		map->position.y_angle = 0;
		map->position.z_angle = 0;
		map->position.isometric_angle = 45;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_MULTIPLY))
		map->position.z_factor *= 1.1;
	if (mlx_is_key_down(map->mlx, MLX_KEY_KP_DIVIDE))
		map->position.z_factor /= 1.1;

	mlx_delete_image(map->mlx, map->mlx_image);
	map->mlx_image = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(map->mlx, map->mlx_image, 0, 0);
	randomize(map);
}