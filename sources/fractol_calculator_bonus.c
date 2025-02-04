/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_calculator_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:35:32 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/29 08:55:19 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

/* 
 * mandelbrot_set():  
 * Calculates the number of iterations for a given point in the Mandelbrot set.  
 * - The point is iterated to check if it escapes the boundary of 4 (2^2).
 * - If it escapes before reaching the maximum number of iterations, the
 function returns the number of iterations.  
 */

int	mandelbrot_set(t_complex c)
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
		z.im = 2 * z.real * z.im + c.im;
		z.real = real_component;
		iteration++;
	}
	return (iteration);
}

/*  
 * julia_set():  
 * Calculates the number of iterations for a given point in the Julia set.  
 * - The point is iterated to check if it escapes the boundary of 4 (2^2). 
 * - If it escapes before reaching the maximum number of iterations, the
 function returns the number of iterations.  
 */

int	julia_set(t_complex c, t_complex z)
{
	double		real_component;
	int			iteration;

	iteration = 0;
	while (((z.real * z.real + z.im * z.im) <= 4)
		&& (iteration < MAX_ITERATION))
	{
		real_component = (z.real * z.real) - (z.im * z.im) + c.real;
		z.im = 2 * z.real * z.im + c.im;
		z.real = real_component;
		iteration++;
	}
	return (iteration);
}
