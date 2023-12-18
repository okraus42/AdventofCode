/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p18.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/18 12:49:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void ok_fill_left(int *x, int *y, unsigned int map[720][650], int len, int val)
{
	while (len)
	{
		map[*y][*x - 1] = val;
		--(*x);
		--len; 
	}
}

void ok_fill_right(int *x, int *y, unsigned int map[720][650], int len, int val)
{
	while (len)
	{
		map[*y][*x + 1] = val;
		++(*x);
		--len; 
	}
}

void ok_fill_up(int *x, int *y, unsigned int map[720][650], int len, int val)
{
	while (len)
	{
		map[*y - 1][*x] = val;
		--(*y);
		--len; 
	}
}

void ok_fill_down(int *x, int *y, unsigned int map[720][650], int len, int val)
{
	while (len)
	{
		map[*y + 1][*x] = val;
		++(*y);
		--len; 
	}
}

void	ok_flood(unsigned int map[720][650], int y, int x, int val);

void	ok_flood(unsigned int map[720][650], int y, int x, int val)
{
	if (map[y][x])
		return ;
	map[y][x] = val;
	ok_flood(map, y - 1, x, val);
	ok_flood(map, y + 1, x, val);
	ok_flood(map, y, x - 1, val);
	ok_flood(map, y, x + 1, val);
}

unsigned int ok_get_colour(char *str)
{
	int	i;

	i = 3;
	while (str[i] != '#')
		++i;
	++i;
	return (ft_atoi_base("0123456789abcdef", &str[i]));
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	unsigned int	map[720][650];
	long long		r;
	int				x;
	int				y;


	r = 0;
	j = 0;
	i = 0;
	while (j < 720)
	{
		i = 0;
		while(i < 650)
		{
			map[j][i] = 0;
			++i;
		}
		++j;
	}
	j = 0;
	x = 310;
	y = 300;
	map[y][x] = 0x1000000;
	while (line[j])
	{
		if (line[j][0] == 'L')
		{
			ok_fill_left(&x, &y, map, ft_atoi(&line[j][2]), 0x1000000 | ok_get_colour(line[j]));
		}
		if (line[j][0] == 'D')
		{
			ok_fill_down(&x, &y, map, ft_atoi(&line[j][2]), 0x1000000 | ok_get_colour(line[j]));
		}
		if (line[j][0] == 'U')
		{
			ok_fill_up(&x, &y, map, ft_atoi(&line[j][2]), 0x1000000 | ok_get_colour(line[j]));
		}
		if (line[j][0] == 'R')
		{
			ok_fill_right(&x, &y, map, ft_atoi(&line[j][2]), 0x1000000 | ok_get_colour(line[j]));
		}

		++j;
	}
	//update starting condition
	//floodfill
	ok_flood(map, 200, 357, 0x1000000);
	//ok_fillheatmap(line, heatmap);
	i = 0;
	j = 0;
	while (j < 720)
	{
		i = 0;
		while(i < 600)
		{
			if (map[j][i])
			{
				if (map[j][i] & 0xFFFFFF)
					ft_printf("%^*C  %C", map[j][i] & 0xFFFFFF);
				else
					ft_printf("%^*C  %C", 0x882200);
				r += 1;
			}
			else
				ft_printf("  ");
			// if (i && j && heatmap[j][i] == heatmap[j][i - 1] + line[j][i] - '0')
			// 	ft_printf("%^*C%3i %C", 0X220022, heatmap[j][i]);
			// else
			++i;
		}
		ft_printf("\n");
		++j;
	}
	*ptot = r;
}


void	ok_update2(char **line, long long *ptot, int i, int j)
{
	long long		r;
	long long		x1;
	long long		y1;
	long long		x2;
	long long		y2;
	long long		n;
	long long		sx;
	long long		sy;
	long long		perimeter;


	r = 0;
	j = 0;
	i = 0;

	perimeter = 0;
	sx = 0;
	sy = 0;
	x1 = sx;
	y1 = sy;
	x2 = sx;
	y2 = sy;
	while (line[j])
	{
		i = 0;
		x1 = x2;
		y1 = y2;
		while (line[j][i] != '#')
			++i;
		++i;
		n = ft_atoi_base("0123456789abcdef", &line[j][i]);
		//ft_printf("s = %s\n", &line[j][i]);
		//ft_printf("n = %lli\n", n);
		//ft_printf("n >> 4 = %lli\n", n >> 4);
		if ((n & 3) == 0)
		{
			x2 = x1 + (n >> 4);
		}
		else if ((n & 3) == 1)
		{
			y2 = y1 + (n >> 4);
		}
		else if ((n & 3) == 2)
		{
			x2 = x1 - (n >> 4);
		}
		else if ((n & 3) == 3)
		{
			y2 = y1 - (n >> 4);
		}
		perimeter += n >> 4;
		r += x1 * y2 - x2 * y1;
		//ft_printf("%lli * %lli - %lli * %lli\n", x1, y2, x2, y1);
		//ft_printf("%lli %lli\n", r, perimeter);
		++j;
	}
	//update starting condition
	//floodfill
	//ok_fillheatmap(line, heatmap);
	r += sx * y2 - x2 * sy;
	r /= 2;
	r += perimeter / 2 + 1;
	*ptot = r;
}


int	main(void)
{
	char		**line;
	//char		**lines;
	int			i;
	int			j;
	long long	total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
	//lines = ft_split(line[0], '');
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
