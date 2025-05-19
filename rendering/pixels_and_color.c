/* ************************************************************************** */
/*					*/
/*			  :::	::::::::   */
/*   pixels_and_color.c   :+:   :+:   :+:   */
/*			  +:+ +:+	+:+   */
/*   By: ycantin <ycantin@student.42.fr>			+#+  +:+	   +#+  */
/*			+#+#+#+#+#+   +#+  */
/*   Created: 2024/12/18 17:45:39 by ycantin		   #+#  #+#	*/
/*   Updated: 2024/12/18 17:52:56 by ycantin		  ###   ########.fr */
/*					*/
/* ************************************************************************** */

#include "../includes/main.h"

unsigned int	rgb_to_color(int *rgb)
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	tex_color(int tex_X, int tex_Y, t_texture *t)
{
	int	color;
	int	bpp;
	int	line_len;

	bpp = t->bpp;
	line_len = t->line_len;
	color = *(int *)&t->addr[(tex_X * (bpp / 8)) + (tex_Y * line_len)];
	return (color);
}

void	image_put_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		pixel = (y * img->line_len) + (x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)(pixel + img->img_pixel_ptr) = color;
	}
}
