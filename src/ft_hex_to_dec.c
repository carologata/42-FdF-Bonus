#include "../include/fdf.h"


void put_alpha(u_int32_t *decimal)
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
/* int main(void)
{
    int result;
    char *str = "1E6"; //486
    // char *str = "2E5C8D0"; //48613584

    result = ft_hex_to_dec(str);
    printf("result %d\n", result);
} */