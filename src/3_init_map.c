#include "../include/fdf.h"

void	find_width(char *map_name, uint32_t *width)
{
	int		i;
	int		fd;
	char	*gnl_line;
	char	**split_line;

	fd = check_fd(map_name);
	*width = 0;
	gnl_line = get_next_line(fd);
	split_line = ft_split(gnl_line, ' ');
	i = 0;
	while (split_line[i] != NULL)
	{
		*width += 1;
		i++;
	}
	if (gnl_line != NULL)
		free(gnl_line);
	free_matrix((void **)split_line);
	get_next_line(-1);
	close(fd);
}

void	find_height(char *map_name, uint32_t *height)
{
	int		fd;
	char	*gnl_line;

	fd = check_fd(map_name);
	*height = 0;
	gnl_line = get_next_line(fd);
	while (gnl_line != NULL)
	{
		*height += 1;
		free(gnl_line);
		gnl_line = get_next_line(fd);
	}
	get_next_line(-1);
	close(fd);
}

void	check_width_vs_count(int width, int count)
{
	if (count != width)
	{
		get_next_line(-1);
		error("invalid map. It is not rectangular.");
	}
}

void	check_map(char *map_name, uint32_t width, uint32_t height)
{
	int			fd;
	uint32_t	h;
	int			i;
	int			count;
	char		*gnl_line;
	char		**split_line;

	fd = check_fd(map_name);
	h = 0;
	while (h < height)
	{
		gnl_line = get_next_line(fd);
		split_line = ft_split(gnl_line, ' ');
		count = 0;
		i = 0;
		while (split_line[i])
		{
			if (ft_strncmp(split_line[count], "\n", 2) != 0)
				count++;
			i++;
		}
		free(gnl_line);
		free_matrix((void **)split_line);
		check_width_vs_count(width, count);
		h++;
	}
	close(fd);
}


uint32_t get_color(char *split_line)
{
	char *str_color;
	uint32_t color;

	str_color = ft_strchr(split_line, ',');
	if(str_color != NULL)
		color = ft_hex_to_dec(str_color);
	else
		color = 0xFFFFFFFF;
	return (color);
}


t_map	*initialize_matrix(char *map_name, t_map *map, uint32_t width,
		uint32_t height)
{
	int			fd;
	uint32_t	h;
	uint32_t	w;
	char		*gnl_line;
	char		**split_line;

	fd = check_fd(map_name);
	map = malloc(sizeof(t_map) * 1);
	if (map == NULL)
		return (NULL);
	map->matrix = malloc(sizeof(t_matrix *) * (height + 1));
	if (map->matrix == NULL)
	{
		free(map->matrix);
		return (NULL);
	}
	h = 0;
	while (h < height)
	{
		gnl_line = get_next_line(fd);
		split_line = ft_split(gnl_line, ' ');
		map->matrix[h] = malloc(sizeof(t_matrix) * width);
		w = 0;
		while (w < width)
		{
			map->matrix[h][w].x = w;
			map->matrix[h][w].y = h;
			map->matrix[h][w].z = ft_atoi(split_line[w]);
			map->matrix[h][w].color = get_color(split_line[w]);
			w++;
		}
		free(gnl_line);
		free_matrix((void **)split_line);
		h++;
	}
	map->matrix[h] = NULL;
	return (map);
}

t_map	*init_map(char *map_name)
{
	uint32_t	width;
	uint32_t	height;
	t_map		*map;

	map = NULL;
	find_width(map_name, &width);
	printf("\nwidth: %d\n", width);
	find_height(map_name, &height);
	printf("height: %d\n", height);
	check_map(map_name, width, height);
	map = initialize_matrix(map_name, map, width, height);
	map->width = width;
	map->height = height;
	return (map);
}
