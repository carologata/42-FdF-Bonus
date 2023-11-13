#include "../include/fdf.h"

void	scale(t_coordinate *point, t_map *map)
{
	point->x *= map->position.scale;
	point->y *= map->position.scale;
	point->z *= map->position.scale * map->position.z_factor;
}

void	translate(t_coordinate *point, t_map *map)
{
	point->x += map->position.x_offset;
	point->y += map->position.y_offset;
}

void	put_valid_pixel(t_map *map, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(map->mlx_image, x, y, color);
}

void	bresenham(t_coordinate *point_1, t_coordinate *point_2, t_map *map)
{
	t_bres	aux;
	int		i;
	int		x1;
	int		y1;
	uint32_t		color;

	aux.dx = point_2->x - point_1->x;
	aux.dy = point_2->y - point_1->y;
	aux.abs_dx = abs(aux.dx);
	aux.abs_dy = abs(aux.dy);
	x1 = point_1->x;
	y1 = point_1->y;	
	color = point_1->color;

	if (aux.abs_dx > aux.abs_dy)
	{
		aux.p = 2 * aux.dy - aux.dx;
		i = 0;
		while (i < aux.abs_dx)
		{
			x1 = aux.dx < 0 ? (x1 - 1) : (x1 + 1);
			if (aux.p < 0)
				aux.p = aux.p + 2 * aux.abs_dy;
			else
			{
				y1 = aux.dy < 0 ? (y1 - 1) : (y1 + 1);
				aux.p = aux.p + (2 * aux.abs_dy - 2 * aux.abs_dx);
			}
			put_valid_pixel(map, x1, y1, color);
			i++;
		}
	}
	else
	{
		aux.p = 2 * aux.dx - aux.dy;
		i = 0;
		while (i < aux.abs_dy)
		{
			y1 = aux.dy < 0 ? (y1 - 1) : (y1 + 1);
			if (aux.p < 0)
				aux.p = aux.p + 2 * aux.abs_dx;
			else
			{
				x1 = aux.dx < 0 ? (x1 - 1) : (x1 + 1);
				aux.p = aux.p + (2 * aux.abs_dx - 2 * aux.abs_dy);
			}
			put_valid_pixel(map, x1, y1, color);
			i++;
		}
	}
}

void	transform(int x1, int y1, char type, t_map *map)
{
	t_coordinate	point_1;
	t_coordinate	point_2;

	point_1.x = map->matrix[y1][x1].x;
	point_1.y = map->matrix[y1][x1].y;
	point_1.z = map->matrix[y1][x1].z;
	point_1.color = map->matrix[y1][x1].color;
	if (type == 'w')
	{
		point_2.x = map->matrix[y1][x1 + 1].x;
		point_2.y = map->matrix[y1][x1 + 1].y;
		point_2.z = map->matrix[y1][x1 + 1].z;
	}
	else
	{
		point_2.x = map->matrix[y1 + 1][x1].x;
		point_2.y = map->matrix[y1 + 1][x1].y;
		point_2.z = map->matrix[y1 + 1][x1].z;
	}
	scale(&point_1, map);
	scale(&point_2, map);
	
	rotation_in_z(&point_1, map);
	rotation_in_z(&point_2, map);
	rotation_in_x(&point_1, map);
	rotation_in_x(&point_2, map);
	rotation_in_y(&point_1, map);
	rotation_in_y(&point_2, map);
	oblique(&point_1, map);
	oblique(&point_2, map);
	translate(&point_1, map);
	translate(&point_2, map);
	bresenham(&point_1, &point_2, map);
}

void	randomize(t_map *map)
{
	uint32_t	w;
	uint32_t	h;

	h = 0;
	while (h < map->height)
	{
		w = 0;
		while (w < map->width)
		{
			if ((w + 1) < map->width)
				transform(w, h, 'w', map);
			if ((h + 1) < map->height)
				transform(w, h, 'h', map);
			w++;
		}
		h++;
	}
}
