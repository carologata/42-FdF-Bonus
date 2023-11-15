#include "../../include/fdf.h"

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
	while (h++ < height)
	{
		gnl_line = get_next_line(fd);
		split_line = ft_split(gnl_line, ' ');
		count = 0;
		i = 0;
		while (split_line[i++])
		{
			if (ft_strncmp(split_line[count], "\n", 2) != 0)
				count++;
		}
		free(gnl_line);
		free_matrix((void **)split_line);
		check_width_vs_count(width, count);
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