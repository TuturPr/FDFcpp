/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   fdf.hpp                                           *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 16:43:59 by arthur            *                 *    */
/*   Updated: 2025/11/03 17:46:36 by arthur            *******************    */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "MLX42.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_data
{
	mlx_t *mlx;
	std::vector<std::vector<int> > map;
	int width;
	int height;

} t_data;

void parse_map(const std::string &file, std::vector<std::vector<int> > &grid);
