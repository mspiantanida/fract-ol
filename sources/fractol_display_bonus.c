/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_display_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:36:08 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/29 08:55:34 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

/*
 * close_window():
 * Closes the window and cleans up resources. It frees the memory associated
 with the image and window, then exits the program.
 */

int	close_window(void *parameter)
{
	t_mlx_data	*data;

	data = (t_mlx_data *)parameter;
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->mlx_window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (0);
	return (0);
}

/*
 * zoom_in_and_out():
 * Handles mouse wheel zooming in and out. It adjusts the zoom factor based
 on the mouse position and updates the fractal view accordingly.
 */

int	zoom_in_and_out(int button, int x, int y, void *parameter)
{
	t_fractal	*fractal;
	double		zoom_scale;
	double		mouse_x;
	double		mouse_y;

	fractal = (t_fractal *)parameter;
	zoom_scale = 1.1;
	mouse_x = (x - WIDTH / 2) / (100.0 * fractal->zoom_factor)
		+ fractal->offset_x;
	mouse_y = (y - HEIGHT / 2) / (100.0 * fractal->zoom_factor)
		+ fractal->offset_y;
	if (button == 4)
		fractal->zoom_factor *= zoom_scale;
	else if (button == 5)
		fractal->zoom_factor /= zoom_scale;
	fractal->offset_x = mouse_x - (x - WIDTH / 2)
		/ (100.0 * fractal->zoom_factor);
	fractal->offset_y = mouse_y - (y - HEIGHT / 2)
		/ (100.0 * fractal->zoom_factor);
	render_fractal(&fractal->data, fractal);
	mlx_put_image_to_window(fractal->data.mlx, fractal->data.mlx_window,
		fractal->data.image, 0, 0);
	return (0);
}

/*
 * key_actions():
 * Performs actions based on the key pressed, such as panning the fractal, 
 adjusting the color shift, changing palettes, or modifying the fractal degree.
 */

void	key_action(int keysym, t_fractal *fractal, double move_step)
{
	if (keysym == 65361)
		fractal->offset_x -= move_step;
	else if (keysym == 65363)
		fractal->offset_x += move_step;
	else if (keysym == 65362)
		fractal->offset_y -= move_step;
	else if (keysym == 65364)
		fractal->offset_y += move_step;
	else if (keysym == 'c')
		fractal->color_shift += 0.25;
	else if (keysym == 'x' && fractal->color_shift > 0.25)
		fractal->color_shift -= 0.25;
	else if (keysym == 'p')
	{
		fractal->palette_index++;
		if (fractal->palette_index >= 6)
			fractal->palette_index = 0;
	}
	else if (keysym == 'm')
		fractal->degree += 1;
	else if (keysym == 'b' && fractal->degree > 2)
		fractal->degree -= 1;
	return ;
}

/*
 * handle_keys():
 * Handles key events, such as closing the window or triggering actions
 like zooming and moving the fractal. It updates the display accordingly.
 */

int	handle_keys(int keysym, t_fractal *fractal)
{
	double	move_step;

	move_step = 0.1 / fractal->zoom_factor;
	if (keysym == 65307)
		close_window(&fractal->data);
	else
	{
		key_action(keysym, fractal, move_step);
		render_fractal(&fractal->data, fractal);
		mlx_put_image_to_window(fractal->data.mlx, fractal->data.mlx_window,
			fractal->data.image, 0, 0);
	}
	return (0);
}
