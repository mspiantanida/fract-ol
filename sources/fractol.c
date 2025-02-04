/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:34:21 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/27 08:44:36 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * init_data():
 * Initializes the mlx data structures required for rendering the fractal image.
 * - Initializes the mlx connection and window.
 * - Creates a new image to store the rendered fractal.
 * - Retrieves the image data address for pixel manipulation.
 * - Initializes default values for fractal-related settings such as zoom,
 offset, and color shift.
 */

void	init_data(t_mlx_data *data, t_fractal *fractal)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		exit (1);
	data->mlx_window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!data->mlx_window)
		exit (1);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		exit (1);
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel,
			&data->line_length, &data->end);
	fractal->data = *data;
	fractal->zoom_factor = 1.0;
	fractal->offset_x = 0.0;
	fractal->offset_y = 0.0;
	fractal->color_shift = 1.0;
	fractal->palette_index = 0;
}

/*
 * Main function to initialize, render, and display a fractal.
 * It checks the user-provided input, sets up interactive controls and event 
 * handling for zoom, key presses, and window closure.
 */

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc < 2)
	{
		write (1, "Usage:\n./fractol mandelbrot\n"
			"./fractol julia <0.000> <0.000>\n", 66);
		exit (1);
	}
	else
		parse_input(argc, argv, &fractal);
	init_data(&fractal.data, &fractal);
	render_fractal(&fractal.data, &fractal);
	mlx_put_image_to_window(fractal.data.mlx, fractal.data.mlx_window,
		fractal.data.image, 0, 0);
	mlx_key_hook(fractal.data.mlx_window, handle_keys, &fractal);
	mlx_mouse_hook(fractal.data.mlx_window, zoom_in_and_out, &fractal);
	mlx_hook(fractal.data.mlx_window, 17, 0, close_window, &fractal.data);
	mlx_loop(fractal.data.mlx);
	return (0);
}
