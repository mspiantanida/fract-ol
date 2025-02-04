/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_calculator_extra_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:35:32 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/29 08:56:38 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

/*  
 * burning_ship_set():  
 * Calculates the number of iterations for a given point in the Burning
 Ship fractal.
 * Similar to the Mandelbrot set, but with additional modification where
 the real and imaginary components are taken as absolute values.  
 */

int	burning_ship_set(t_complex c)
{
	t_complex	z;
	double		real_component;
	int			iteration;

	z.real = 0;
	z.im = 0;
	iteration = 0;
	while (((z.real * z.real + z.im * z.im) <= 4)
		&& (iteration < MAX_ITERATION))
	{
		real_component = (z.real * z.real) - (z.im * z.im) + c.real;
		z.im = fabs(2 * z.real * z.im) + c.im;
		z.real = fabs(real_component);
		iteration++;
	}
	return (iteration);
}

/*  
 * tricorn_set(): 
 * - Calculates the number of iterations for a given point in the Tricorn
 fractal.  
 * - Similar to the Mandelbrot set, but with a negative imaginary part in the 
 iteration equation.  
 */

int	tricorn_set(t_complex c)
{
	t_complex	z;
	double		real_component;
	int			iteration;

	z.real = 0;
	z.im = 0;
	iteration = 0;
	while (((z.real * z.real + z.im * z.im) <= 4)
		&& (iteration < MAX_ITERATION))
	{
		real_component = (z.real * z.real) - (z.im * z.im) + c.real;
		z.im = -2 * z.real * z.im + c.im;
		z.real = real_component;
		iteration++;
	}
	return (iteration);
}

/*  
 * calculate_multibrot():  
 * Calculates the next iteration for the Multibrot set with a given degree.  
 * Uses polar coordinates and raises the magnitude to the given degree before
 recomputing the real and imaginary parts.  
 */

t_complex	calculate_multibrot(t_complex z, t_complex c, int degree)
{
	t_complex	result;
	double		real_temp;

	result.real = z.real;
	result.im = z.im;
	while (--degree > 0)
	{
		real_temp = result.real * z.real - result.im * z.im;
		result.im = result.real * z.im + result.im * z.real;
		result.real = real_temp;
	}
	result.real += c.real;
	result.im += c.im;
	return (result);
}

/*
 * multibrot_set():  
 * Calculates the number of iterations for a given point in the Multibrot set.  
 * Similar to other fractals, but the iteration is based on a complex number
 raised to the specified degree.  
 */

int	multibrot_set(t_complex c, int degree)
{
	t_complex	z;
	int			iteration;
	int			max_iteration;

	z.real = 0;
	z.im = 0;
	iteration = 0;
	max_iteration = MAX_ITERATION / 2;
	while (((z.real * z.real + z.im * z.im) <= 4)
		&& (iteration < max_iteration))
	{
		z = calculate_multibrot(z, c, degree);
		iteration++;
	}
	return (iteration);
}
