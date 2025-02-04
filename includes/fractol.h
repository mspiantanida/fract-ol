/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:35 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/30 11:39:33 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# define HEIGHT 540
# define WIDTH 960
# define MAX_ITERATION 1000 

typedef struct s_palette
{
	double	red_comp;
	double	green_comp;
	double	blue_comp;
//	t_palette	
}		t_palette;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*mlx_window;
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		end;
}	t_mlx_data;

typedef struct s_complex
{
	double	real;
	double	im;
}		t_complex;

typedef struct s_fractal
{
	t_mlx_data	data;
	t_complex	julia_constant;
	double		zoom_factor;
	double		offset_x;
	double		offset_y;
	double		color_shift;
	int			type;
	int			palette_index;
}		t_fractal;

// Fractol render
void	init_palettes(t_palette *palettes);	
void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
void	render_fractal(t_mlx_data *data, t_fractal *fractal);
int		calculate_fractal_iteration(t_fractal *fractal, int x, int y);
int		get_color(int iteration, t_fractal *fractal, const t_palette *palette);

// Fractol display
int		close_window(void *parameter);
int		zoom_in_and_out(int button, int x, int y, void *parameter);
int		handle_keys(int keysym, t_fractal *fractal);
void	key_action(int keysym, t_fractal *fractal, double move_step);

// Fractol calculator
int		mandelbrot_set(t_complex c);
int		julia_set(t_complex c, t_complex z);

// Fractol input
double	parse_fraction_part(const char **args);
double	get_number(const char *args);
void	init_data(t_mlx_data *data, t_fractal *fractal);
void	parse_input(int argc, char **argv, t_fractal *fractal);

#endif
