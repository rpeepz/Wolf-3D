/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:04:46 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/08 19:55:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** struct for mlx image pointer,
** camera variables,
** pixel variables
*/

typedef struct			s_image
{
	void				*image;
	char				*pixels;
	int					bpp;
	int					stride;
	int					endian;
}						t_image;

typedef struct			s_camera
{
	double				offsetx;
	double				offsety;
	double				offsetz;
	double				zoom;
	int					scale;
}						t_camera;

typedef struct			s_pix
{
	double				a;
	double				b;
	double				w;
	double				h;
	double				xmin;
	double				xmax;
	double				ymin;
	double				ymax;
	double				c[2];
	int					color[3];
}						t_pix;

#endif
