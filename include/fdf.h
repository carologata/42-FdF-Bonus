#ifndef FDF_H
# define FDF_H

# define WIDTH 1280
# define HEIGHT 720

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "../lib/libft/libft.h"
# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_matrix
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}				t_matrix;

typedef struct s_position
{
	double		scale;
	double		z_factor;
	int			x_offset;
	int			y_offset;
	double		x_angle;
	double		y_angle;
	double		z_angle;
	double		isometric_angle;
}				t_position;

typedef struct s_map
{
	uint32_t	width;
	uint32_t	height;
	t_matrix	**matrix;
	t_position	position;
	mlx_t		*mlx;
	mlx_image_t	*mlx_image;
}				t_map;

typedef struct s_coordinate
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}				t_coordinate;

typedef struct s_bres
{
	int			dx;
	int			dy;
	int			abs_dx;
	int			abs_dy;
	int			p;
}				t_bres;

//init MLX42 and check args
void			check_args(int argc, char *map_name);
mlx_t			*init_mlx(void);
mlx_image_t		*init_image(mlx_t *mlx);
int				init_window(mlx_t *mlx, mlx_image_t *mlx_image);

//init map
t_map			*init_map(char *map_name);
t_map			*initialize_matrix(char *map_name, uint32_t width,
					uint32_t height);
void			init_each_line(int fd, uint32_t h, uint32_t width, t_map *map);
void			find_width(char *map_name, uint32_t *width);
void			find_height(char *map_name, uint32_t *height);
void			check_width_vs_count(int width, int count);
void			check_map(char *map_name, uint32_t width, uint32_t height);
uint32_t		get_color(char *split_line);

//init position
void			find_initial_scale(t_map *map);
void			centralize(t_map *map);
void			find_z_factor(t_map *map);
void			init_position(t_map *map);

//transformations and randomize
void			put_valid_pixel(t_map *map, int x, int y, uint32_t color);
void			bresenham(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			slope_lower_1(t_bres *aux, t_coordinate *point, t_map *map);
void			slope_bigger_equal_1(t_bres *aux, t_coordinate *point,
					t_map *map);
void			init_points(int x1, int y1, char type, t_map *map);
void			transform(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			randomize(t_map *map);
void			scale(t_coordinate *point_1, t_coordinate *point_2, t_map *map);
void			rotation_in_x(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			rotation_in_y(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			rotation_in_z(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			oblique(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);
void			translate(t_coordinate *point_1, t_coordinate *point_2,
					t_map *map);

//utils
void			error(char *err);
void			free_matrix(void **matrix);
int				check_fd(char *map_name);
void			put_alpha(uint32_t *decimal);
uint32_t		ft_hex_to_dec(char *str);

//bonus
void			ft_hook(void *param);

#endif