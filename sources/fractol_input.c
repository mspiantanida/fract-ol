/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:35:06 by mpiantan          #+#    #+#             */
/*   Updated: 2025/01/20 11:35:09 by mpiantan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
 * parse_fraction_part():
 * Parses the fractional part of a number from a string.
 * - Expects the string to point to the character after the decimal point ('.').
 * - Converts the digits after the decimal point into a fractional value.
 * - Divides the result by the appropriate power of 10 based on the number of 
 digits.
 */

double	parse_fraction_part(const char **args)
{
	double	fraction_result;
	int		divisor;

	fraction_result = 0.0;
	divisor = 1;
	if (**args == '.')
	{
		(*args)++;
		while (**args >= '0' && **args <= '9')
		{
			fraction_result = fraction_result * 10 + (**args - '0');
			divisor *= 10;
			(*args)++;
		}
	}
	return (fraction_result / divisor);
}

/*
 * get_number():
 * Parses a string and converts it to a double.
 * - Handles optional '+' or '-' signs at the beginning of the string.
 * - Processes both the integer and fractional parts of the number.
 * - Validates the input format and exits with an error if invalid characters 
 are found.
 */

double	get_number(const char *args)
{
	double	result;
	int		sign;

	sign = 1;
	result = 0.0;
	if (*args == '-' || *args == '+')
	{
		if (*args == '-')
		{
			sign = -sign;
			args++;
		}
	}
	while (*args >= '0' && *args <= '9')
	{
		result = result * 10 + (*args - '0');
		args++;
	}
	result += parse_fraction_part(&args);
	if (*args != '\0')
	{
		write(1, "Error: Invalid number format\n", 29);
		exit (1);
	}
	return (result * sign);
}

/*
 * parse_input():
 * Parses and validates the user input to determine the fractal type.
 * - Ensures the input matches a valid fractal name (e.g., mandelbrot,
 julia, etc.).
 * - For "julia," extracts and assigns the real and imaginary parts of
 the constant.
 * - If the input is invalid, displays usage instructions and exits the program.
 */

void	parse_input(int argc, char **argv, t_fractal *fractal)
{
	t_complex	c;

	if (argc == 2 && ft_strncmp(argv[1], "mandelbrot", 10) == 0
		&& ft_strlen(argv[1]) == 10)
		fractal->type = 1;
	else if (ft_strncmp(argv[1], "julia", 5) == 0 && argc == 4
		&& ft_strlen(argv[1]) == 5)
	{
		c.real = get_number(argv[2]);
		c.im = get_number(argv[3]);
		if (fabs(c.real) > 2.0 || fabs(c.im) > 2.0)
		{
			write(1, "Error: number must be between -2 and 2\n", 39);
			exit(1);
		}
		fractal->julia_constant = c;
		fractal->type = 2;
	}
	else
	{
		write (1, "Invalid argument.\nUsage:\n./fractol mandelbrot\n"
			"./fractol julia <0.000> <0.000>\n", 78);
		exit (1);
	}
}
