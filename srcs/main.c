/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spgibber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:17:02 by spgibber          #+#    #+#             */
/*   Updated: 2022/04/14 13:17:05 by spgibber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	win_init(t_fractol *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		error("ERROR: Can\'t initialize window\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "FRACTOL");
	if (!data->win_ptr)
		error("ERROR: Can\'t initialize window\n");
	data->image = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->image)
		error("ERROR: Can\'t initialize image\n");
	data->data_addr = mlx_get_data_addr(data->image,
			&data->bits_per_pixel, &data->line_length,
			&data->endian);
	if (!data->data_addr)
		error("ERROR: Can\'t initialize image\n");
	mlx_expose_hook(data->win_ptr, ft_expose_hook, data);
	mlx_key_hook(data->win_ptr, ft_key_hook, data);
	mlx_hook(data->win_ptr, KEY_CROSS, MASK_CROSS, ft_close_window, data);
	mlx_mouse_hook(data->win_ptr, ft_mouse_hook, data);
}

static t_complex	init_parameters(double a, double b)
{
	t_complex	k;

	k.re = a;
	k.im = b;
	return (k);
}

void	init_fractal(t_fractol *data, t_complex *k)
{
	data->color[0] = 3;
	data->color[1] = 9;
	data->color[2] = 7;
	data->x0 = -500;
	data->y0 = 500;
	data->scale = 250;
	if (data->type == 1 || data->type == 3)
		*k = init_parameters(0, 0);
	else if (data->type == 2)
		*k = init_parameters(0.367811, 0.367811);
	else if (data->type == 0)
		*k = init_parameters(data->arg1, data->arg2);
	data->arg1 = k->re;
	data->arg2 = k->im;
}

int	main(int argc, char **argv)
{
	t_fractol	*data;
	t_complex	k;

	data = (t_fractol *)malloc(sizeof(t_fractol));
	if (!data)
		error("ERROR: Problems with memory\n");
	check_arguments(data, argc, argv);
	init_fractal(data, &k);
	win_init(data);
	mlx_loop(data->mlx_ptr);
	free (data);
	return (0);
}
