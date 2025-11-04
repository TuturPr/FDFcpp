/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   render.cpp                                        *        *        *    */
/*                                                     * *    *   *    * *    */
/*   By: arthur <arthur@student.42.fr>                 *    *       *    *    */
/*                                                     *                 *    */
/*   Created: 2025/11/03 17:45:57 by arthur            *                 *    */
/*   Updated: 2025/11/04 02:30:06 by arthur            *******************    */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.hpp"
#include <cmath>
#include <climits>

static void draw_pixel_safe(t_data *data, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		mlx_put_pixel(data->img, x, y, color);
}

static void get_dimensions(t_data *data)
{
	data->height = data->map.size();
	data->width = data->map[0].size();
	data->altitude = 2;
}

static void calculate_zoom(t_data *data)
{
	double zoom_x = (double)WIN_WIDTH / (data->width + data->height);
	double zoom_y = (double)WIN_HEIGHT / (data->width + data->height);
	data->zoom = (int)(fmin(zoom_x, zoom_y) * 1.7);
	if (data->zoom < 1) data->zoom = 1;
}

static void calculate_offsets(t_data *data)
{
	double angle = 0.523599; // 30°
	double cos_a = cos(angle);
	double sin_a = sin(angle);

	int min_x = INT_MAX, max_x = INT_MIN;
	int min_y = INT_MAX, max_y = INT_MIN;

	for (int i = 0; i < data->height; ++i)
	{
		for (int j = 0; j < data->width; ++j)
		{
			int z = data->map[i][j];
			int x = (j - i) * cos_a * data->zoom;
			int y = (i + j) * sin_a * data->zoom - z * data->altitude;
			if (x < min_x) min_x = x;
			if (x > max_x) max_x = x;
			if (y < min_y) min_y = y;
			if (y > max_y) max_y = y;
		}
	}

	data->offset_x = (WIN_WIDTH - (max_x - min_x)) / 2 - min_x;
	data->offset_y = (WIN_HEIGHT - (max_y - min_y)) / 2 - min_y;
}

static void coordinates(t_data *data, int i, int j, int &x, int &y)
{
	int z = data->map[i][j];
	double angle = 0.523599;
	double cos_a = cos(angle);
	double sin_a = sin(angle);

	x = (j - i) * cos_a * data->zoom + data->offset_x;
	y = (i + j) * sin_a * data->zoom - z * data->altitude + data->offset_y;
}

static uint32_t get_color(int z, int min_z, int max_z)
{
	if (z >= 0)
	{
		double ratio = (max_z == 0 ? 1.0 : (double)z / max_z);
		if (ratio > 1.0) ratio = 1.0;
		uint8_t r = 255;
		uint8_t g = (uint8_t)(255 * (1 - ratio));
		uint8_t b = (uint8_t)(255 * (1 - ratio));
		return (0xFF << 24) | (r << 16) | (g << 8) | b;
	}
	else
	{
		double ratio = (min_z == 0 ? 1.0 : (double)z / min_z);
		if (ratio > 1.0) ratio = 1.0;
		uint8_t r = (uint8_t)(255 * (1 - ratio));
		uint8_t g = (uint8_t)(255 * (1 - ratio));
		uint8_t b = 255;
		return (0xFF << 24) | (r << 16) | (g << 8) | b;
	}
}

static void draw_line(t_data *data, int x0, int y0, int x1, int y1, uint32_t color0, uint32_t color1)
{
	int dx = abs(x1 - x0), sx = (x0 < x1 ? 1 : -1);
	int dy = -abs(y1 - y0), sy = (y0 < y1 ? 1 : -1);
	int err = dx + dy, e2;

	int length = fmax(abs(x1 - x0), abs(y1 - y0));
	int step = 0;

	while (true)
	{
		double t = (length == 0 ? 0.0 : (double)step / length);
		uint8_t r0 = (color0 >> 16) & 0xFF;
		uint8_t g0 = (color0 >> 8) & 0xFF;
		uint8_t b0 = color0 & 0xFF;

		uint8_t r1 = (color1 >> 16) & 0xFF;
		uint8_t g1 = (color1 >> 8) & 0xFF;
		uint8_t b1 = color1 & 0xFF;

		uint32_t r = r0 + (r1 - r0) * t;
		uint32_t g = g0 + (g1 - g0) * t;
		uint32_t b = b0 + (b1 - b0) * t;

		draw_pixel_safe(data, x0, y0, (0xFF << 24) | (r << 16) | (g << 8) | b);

		if (x0 == x1 && y0 == y1) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
		step++;
	}
}

void render(t_data *data)
{
	get_dimensions(data);
	calculate_zoom(data);
	calculate_offsets(data);

	uint32_t *pixels = (uint32_t *)data->img->pixels;
	for (int i = 0; i < WIN_WIDTH * WIN_HEIGHT; ++i)
		pixels[i] = 0xFF000000;

	int min_z = INT_MAX, max_z = INT_MIN;
	for (int i = 0; i < data->height; ++i)
	{
		for (int j = 0; j < data->width; ++j)
		{
			int z = data->map[i][j];
			if (z < min_z) min_z = z;
			if (z > max_z) max_z = z;
		}
	}

	for (int i = 0; i < data->height; ++i)
	{
		for (int j = 0; j < data->width; ++j)
		{
			int x, y;
			coordinates(data, i, j, x, y);
			uint32_t color = get_color(data->map[i][j], min_z, max_z);

			if (j + 1 < data->width)
			{
				int x1, y1;
				coordinates(data, i, j + 1, x1, y1);
				uint32_t color1 = get_color(data->map[i][j + 1], min_z, max_z);
				draw_line(data, x, y, x1, y1, color, color1);
			}
			if (i + 1 < data->height)
			{
				int x1, y1;
				coordinates(data, i + 1, j, x1, y1);
				uint32_t color1 = get_color(data->map[i + 1][j], min_z, max_z);
				draw_line(data, x, y, x1, y1, color, color1);
			}

			draw_pixel_safe(data, x, y, color);
		}
	}
}
