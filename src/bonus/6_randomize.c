#include "../../include/fdf.h"

void	put_valid_pixel(t_map *map, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(map->mlx_image, x, y, color);
}

void	slope_lower_1(t_bres *aux, t_coordinate *point, t_map *map)
{
	int			x;
	int			y;
	uint32_t	color;
	int			i;

	x = point->x;
	y = point->y;
	color = point->color;
	aux->p = 2 * aux->dy - aux->dx;
	i = 0;
	while (i < aux->abs_dx)
	{
		x = aux->dx < 0 ? (x - 1) : (x + 1);
		if (aux->p < 0)
			aux->p = aux->p + 2 * aux->abs_dy;
		else
		{
			y = aux->dy < 0 ? (y - 1) : (y + 1);
			aux->p = aux->p + (2 * aux->abs_dy - 2 * aux->abs_dx);
		}
		put_valid_pixel(map, x, y, color);
		i++;
	}
}

void	slope_bigger_equal_1(t_bres *aux, t_coordinate *point, t_map *map)
{
	int			x;
	int			y;
	uint32_t	color;
	int			i;

	x = point->x;
	y = point->y;
	color = point->color;
	aux->p = 2 * aux->dx - aux->dy;
	i = 0;
	while (i < aux->abs_dy)
	{
		y = aux->dy < 0 ? (y - 1) : (y + 1);
		if (aux->p < 0)
			aux->p = aux->p + 2 * aux->abs_dx;
		else
		{
			x = aux->dx < 0 ? (x - 1) : (x + 1);
			aux->p = aux->p + (2 * aux->abs_dx - 2 * aux->abs_dy);
		}
		put_valid_pixel(map, x, y, color);
		i++;
	}
}

void	bresenham(t_coordinate *point_1, t_coordinate *point_2, t_map *map)
{
	t_bres	aux;

	aux.dx = point_2->x - point_1->x;
	aux.dy = point_2->y - point_1->y;
	aux.abs_dx = abs(aux.dx);
	aux.abs_dy = abs(aux.dy);
	if (aux.abs_dx > aux.abs_dy)
		slope_lower_1(&aux, point_1, map);
	else
		slope_bigger_equal_1(&aux, point_1, map);
}

void	transform(int x1, int y1, char type, t_map *map)
{
	t_coordinate	point_1;
	t_coordinate	point_2;

	point_1.x = map->matrix[y1][x1].x;
	point_1.y = map->matrix[y1][x1].y;
	point_1.z = map->matrix[y1][x1].z;
	point_1.color = map->matrix[y1][x1].color;
	point_2.x = map->matrix[y1][x1 + 1].x;
	point_2.y = map->matrix[y1][x1 + 1].y;
	point_2.z = map->matrix[y1][x1 + 1].z;
	if (type == 'h')
	{
		point_2.x = map->matrix[y1 + 1][x1].x;
		point_2.y = map->matrix[y1 + 1][x1].y;
		point_2.z = map->matrix[y1 + 1][x1].z;
	}
	scale(&point_1, &point_2, map);
	rotation_in_z(&point_1, &point_2, map);
	rotation_in_x(&point_1, &point_2, map);
	rotation_in_y(&point_1, &point_2, map);
	oblique(&point_1, &point_2, map);
	translate(&point_1, &point_2, map);
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
