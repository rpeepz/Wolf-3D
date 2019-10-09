/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:32:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/10/08 18:34:18 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/wolf3d.h"

static int	create_map(int height, int width, char *buf, t_map *map)
{
	char	**lines;
	char	**values;

	if (!(lines = ft_strsplit(buf, '\n')))
		return (-42);
	if (!(map->cell = malloc(sizeof(int *) * height)))
		return (del_array(lines, height));
	map->height = -1;
	while (++map->height < height)
	{
		if (!(values = ft_strsplit(lines[map->height], ' ')))
			return (del_array(lines, height));
		if (!(map->cell[map->height] = malloc(sizeof(int) * width)))
		{
			del_map(map);
			return (del_array(values, width));
		}
		map->width = -1;
		while (++map->width < width)
			map->cell[map->height][map->width] = ft_atoi(values[map->width]);
		del_array(values, width);
	}
	del_array(lines, height);
	return (1);
}

int			validate(char *filename, t_map *map)
{
	char	buf[PAGESIZE + 1];
	char	size[16];
	int		fd;

	if ((fd = open(filename, O_RDONLY)) < 3)
		return (-1);
	ft_bzero(buf, 16);
	ft_bzero(size, 16);
	while (1)
	{
		read(fd, buf, 1);
		if (*buf == '\n')
			break ;
		if (!ft_isdigit(*buf) && *buf != ' ')
			return (-2);
		ft_strncpy(&size[LEN(size)], buf, 1);
	}
	ft_bzero(buf, PAGESIZE + 1);
	read(fd, buf, 4096);
	close(fd);
	return (create_map(ft_atoi(size), ft_atoi(ft_strchr(size, ' ')), buf, map));
}
