/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   main.cpp                                          *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 16:43:36 by arthur            *                 *    */
/*   Updated: 2025/11/03 17:43:55 by arthur            *******************    */
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
	parse_map(argv[1], data->map);
	print_map(data->map);
	return (0);
}
