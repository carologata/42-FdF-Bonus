#include "../../include/fdf.h"

void put_alpha(uint32_t *decimal)
{   
    *decimal = *decimal << 8 | 0x000000FF;
}

uint32_t ft_hex_to_dec(char *str)
{
    char hex;
    int aux;
    uint32_t decimal;
    int i;

    i = 0;
    decimal = 0;
    while(str[i] != '\0' && str[i] != '\n' && str[i] != ' ')
    {
        hex = str[i];
        if(hex >= '0' && hex <= '9')
            aux = hex - 48;
        else if(hex >= 'a' && hex <= 'f')
            aux = hex - 87;
        else if(hex >= 'A' && hex <= 'F')
            aux = hex - 55;
        decimal = decimal << 4 | aux;
        i++;
    }

    put_alpha(&decimal);
    return (decimal);
}

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
