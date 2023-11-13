#include "../include/fdf.h"

void rotation_in_x(t_coordinate *point, t_map *map)
{
    int y;
    int z;
    double pi;
    double angle;

    pi = M_PI;
    angle = map->position.x_angle * pi / 180;

    y = point->y;
    z = point->z;

    point->y = (y * cos(angle)) - (z * sin(angle));
    point->z = (y * sin(angle)) + (z * cos(angle));
}

void rotation_in_y(t_coordinate *point, t_map *map)
{
    int x;
    int z;
    double pi;
    double angle;

    pi = M_PI;
    angle = map->position.y_angle * pi / 180;

    x = point->x;
    z = point->z;

    point->x = (x * cos(angle)) + (z * sin(angle));
    point->z = (-x * sin(angle)) + (z * cos(angle));
}

void rotation_in_z(t_coordinate *point, t_map *map)
{
    int x;
    int y;
    double pi;
    double angle;

    pi = M_PI;
    angle = map->position.z_angle * pi / 180;

    x = point->x;
    y = point->y;

    point->x = (x * cos(angle)) - (y * sin(angle));
    point->y = (x * sin(angle)) + (y * cos(angle));
}

void oblique(t_coordinate *point, t_map * map)
{
    int x;
    int y;
    double pi;
    double angle;

    pi = M_PI;
    angle = map->position.isometric_angle * pi / 180;

    x = point->x;
    y = point->y;

    point->x = x + (point->z * sin(angle));
    point->y = y - (point->z * sin(angle));  
}
