/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_console.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:40:38 by rpapagna          #+#    #+#             */
/*   Updated: 2019/11/15 15:30:02 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wolf3d.h"

void	ft_error(int key)
{
	if (key == 1)
		printf("Bad file\n");
	else if (key == 2)
		printf("Invalid map header\n");
	else if (key == 42)
		printf("Malloc Error\n");
	else
		printf("Invalid map [%d]\n", key);
}

int		ft_out(int key)
{
	if (key <= 0)
		ft_error(-key);
	else if (key == KEY_PLUS)
		printf("z axis '+' ");
	else if (key == KEY_MINUS)
		printf("z axis '-' ");
	else if (key == KEY_UP)
		printf("UP\n");
	else if (key == KEY_DOWN)
		printf("DOWN\n");
	else if (key == KEY_LEFT)
		printf("LEFT\n");
	else if (key == KEY_RIGHT)
		printf("RIGHT\n");
	else if (key == SCROLL_UP)
		printf("Zoom level + ");
	else if (key == SCROLL_DOWN)
		printf("Zoom level - ");
	else if (key == PG_UP)
		printf("Zoom level + ");
	else if (key == PG_DOWN)
		printf("Zoom level - ");
	else if (key == KEY_R)
		printf("Reset offset, zoom, scale\n");
	return (1);
}

int		ft_help(void)
{
	ft_printf("Controls:\n");
	ft_printf("%11s\t\n", "Arrow Keys");
	ft_printf("%11s\tMove forward\n", "UP");
	ft_printf("%11s\tMove backward\n", "DOWN");
	ft_printf("%11s\tTurn\n", "LEFT/RIGHT");
	// ft_printf("%11s\tJump\n", "Space");
	// ft_printf("%11c\tIncrease 'Z'\n%11c\tDecrease 'Z'\n", '+', '-');
	// ft_printf("%11c\tToggle Pause\n", 'P');
	// ft_printf("%11s\tIncrease Zoom\n%11s\tZecrease zoom\n", \
	// "page up", "page down");
	// ft_printf("%11c\tReset position, 'Z' & zoom\n", 'R');
	ft_printf("%11s\tQuit\n", "esc");
	return (1);
}
