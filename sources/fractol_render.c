/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:34:49 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/27 15:19:40 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * init_palettes():
 * Initializes an array of color palettes, each with predefined red, green, 
 and blue components for rendering fractals with different color schemes.
 * palette[0] = shades of blue-cyan
 * palette[0] = shades of purple-red
 * palette[0] = shades of purple-pink
 * palette[0] = shades of red-orange
 * palette[0] = shades of yellow-green
 * palette[0] = shades of green
 */

void	init_palettes(t_palette *palettes)
{
	palettes[0].red_comp = 9.0;
	palettes[0].green_comp = 15.0;
	palettes[0].blue_comp = 8.5;
	palettes[1].red_comp = 15.0;
	palettes[1].green_comp = 4.0;
	palettes[1].blue_comp = 4.0;
	palettes[2].red_comp = 25.0;
	palettes[2].green_comp = 4.0;
	palettes[2].blue_comp = 1.0;
	palettes[3].red_comp = 25.0;
	palettes[3].green_comp = 5.0;
	palettes[3].blue_comp = 2.0;
	palettes[4].red_comp = 25.0;
	palettes[4].green_comp = 15.0;
	palettes[4].blue_comp = 2.0;
	palettes[5].red_comp = 5.0;
	palettes[5].green_comp = 25.0;
	palettes[5].blue_comp = 2.0;
}

/*
 * get_color():
 * Computes the color of a pixel based on the number of iterations for a
 fractal and the selected color palette.
 */

int	get_color(int iteration, t_fractal *fractal, const t_palette *palette)
{
	double	tr;
	int		red;
	int		green;
	int		blue;

	red = 0;
	green = 0;
	blue = 0;
	if (fractal->type == 2)
		tr = (double)iteration / (MAX_ITERATION * 2);
	else
		tr = (double)iteration / (MAX_ITERATION / 2);
	if (iteration == MAX_ITERATION)
		return (0x000000);
	red = (int)(palette->red_comp * (1 - tr) * (1 - tr) * tr * tr
			* 255 * fractal->color_shift);
	green = (int)(palette->green_comp * (1 - tr) * (1 - tr) * tr * tr
			* 255 * fractal->color_shift);
	blue = (int)(palette->blue_comp * (1 - tr) * (1 - tr) * (1 - tr) * tr
			* 255 * fractal->color_shift);
	return (red << 16 | green << 8 | blue);
}

/*
 * my_mlx_pixel_put():
 * Sets the color of a pixel at coordinates (x, y) on the screen by writing
 to the pixel buffer.
 */

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->address
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

/* 
 * calculate_fractal_iteration():
 * Calculates the number of iterations for a point (x, y) on the fractal,
 determining whether it belongs to the fractal set based on the selected
 fractal type.
 */

int	calculate_fractal_iteration(t_fractal *fractal, int x, int y)
{
	t_complex	c;
	t_complex	z;

	c.real = (x - (WIDTH / 2)) / (200.0 * fractal->zoom_factor)
		+ fractal->offset_x;
	c.im = (y - (HEIGHT / 2)) / (200.0 * fractal->zoom_factor)
		+ fractal->offset_y;
	if (fractal->type == 1)
		return (mandelbrot_set(c));
	else if (fractal->type == 2)
	{
		z.real = (x - (WIDTH / 2)) / (200.0 * fractal->zoom_factor)
			+ fractal->offset_x;
		z.im = (y - (HEIGHT / 2)) / (200.0 * fractal->zoom_factor)
			+fractal->offset_y;
		c = fractal->julia_constant;
		return (julia_set(c, z));
	}
	return (0);
}

/*
 * render_fractal():
 * Renders the entire fractal by iterating over each pixel, calculating
 its iteration count, determining its color, and placing it on the screen.
 */

void	render_fractal(t_mlx_data *data, t_fractal *fractal)
{
	int			x;
	int			y;
	int			color;
	int			iteration;
	t_palette	palettes[6];

	init_palettes(palettes);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			iteration = calculate_fractal_iteration(fractal, x, y);
			color = get_color(iteration, fractal,
					&palettes[fractal->palette_index]);
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}
