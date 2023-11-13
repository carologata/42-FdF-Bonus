#include "../include/fdf.h"

// -----------------------------------------------------------------------------
void	error(char *err)
{
	printf("%s\n", err);
	exit (1);
}

void	free_matrix(void **matrix)
{
	int	i;
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int check_fd(char *map_name)
{
	int fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		error("invalid file.");
		return (-1);
	}
	return (fd);
}