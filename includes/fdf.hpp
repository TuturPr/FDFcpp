/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   fdf.hpp                                           *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 16:43:59 by arthur            *                 *    */
/*   Updated: 2025/11/04 02:12:04 by arthur            *******************    */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include "MLX42.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#include <SDL2/SDL_syswm.h>

typedef struct s_data
{
	mlx_t *mlx;
	mlx_image_t *img;
	std::vector<std::vector<int> > map;
	int width;
	int height;
	int offset_x;
	int offset_y;
	int zoom;
	int altitude;

} t_data;

typedef struct s_point
{
	int x;
	int y;
	int z;
} t_point;

void parse_map(const std::string &file, std::vector<std::vector<int> > &grid);
void render(t_data *data);
