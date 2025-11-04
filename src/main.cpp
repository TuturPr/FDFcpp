/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.cpp                                          *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 16:43:36 by arthur            *                 *    */
/*   Updated: 2025/11/04 02:35:05 by arthur            *******************    */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.hpp"

void print_map(const std::vector<std::vector<int> > &map)
{
	for (size_t i = 0; i < map.size(); ++i)
	{
		for (size_t j = 0; j < map[i].size(); ++j)
		{
			std::cout << map[i][j] << " ";
		}
		std::cout << '\n';
	}
}

int main(int argc, char **argv)
{
	t_data	*data = new t_data;
	if (argc != 2)
	{
		std::cout << "usage : ./fdf \".fdf file\"" << '\n';
		return (1);
	}
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "FDF", true);
	if (!data->mlx)
		return (1);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
		return (1);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	parse_map(argv[1], data->map);
	render(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	delete data;
	return (0);
}
