/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 03:40:38 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/01 05:32:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../wolf3d.h"

int		ft_out(int key)
{
	if (key == KEY_PLUS)
		printf("'+'\n");
	else if (key == KEY_MINUS)
		printf("'-'\n");
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
	else if (key == -42)
		printf("Malloc Error\n");
	return (1);
}

int		ft_help(void)
{
	ft_printf("Controls:\n");
	ft_printf("%11s\tMove\n", "arrow keys");
	ft_printf("%11s\tJump\n", "Space");
	ft_printf("%11c\tIncrease 'Z'\n%11c\tDecrease 'Z'\n",
	'+', '-');
	ft_printf("%11c\tToggle mouse lock\n", 'C');
	ft_printf("%11s\tIncrease Zoom\n%11s\tZecrease zoom\n",
	"page up", "page down");
	ft_printf("%11c\tReset position, 'Z' & zoom\n", 'R');
	ft_printf("%11s\tQuit\n", "esc");
	return (1);
}
