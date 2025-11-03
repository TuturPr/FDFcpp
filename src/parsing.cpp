/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   parsing.cpp                                       *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 17:26:27 by arthur            *                 *    */
/*   Updated: 2025/11/03 17:33:45 by arthur            *******************    */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.hpp"

void parse_map(const std::string &file, std::vector<std::vector<int> > &grid)
{
	std::ifstream fs;

	fs.open(file.c_str());
	if (!fs.is_open() || file.find(".fdf") == std::string::npos || file.find(".fdf") + 4 != file.length())
	{
		std::cerr << "Error: Could not open file " << file << '\n';
		return ;
	}
	while (!fs.eof())
	{
		std::string line;
		std::getline(fs, line);
		std::istringstream iss(line);
		std::vector<int> row;
		std::string number;
		while (iss >> number)
			row.push_back(std::atoi(number.c_str()));
		if (!row.empty())
			grid.push_back(row);
	}
	fs.close();
}
