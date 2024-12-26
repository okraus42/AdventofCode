/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p24.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/24 13:53:22 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define HAILS 300	//300

#define INPUT "input"

#define RA 200000000000000			//7 	200000000000000
#define RB 400000000000000			//27	400000000000000

#define ABS(a) ((a > 0) * a + (a < 0) * a)
#define PN(a) ((a > 0) - (a < 0))

//16 bits step count 8 bits y, 8 bits x

typedef struct s_hail
{
	int			collision;
	long double	x;
	long double	y;
	long double	z;
	long double	dx;
	long double	dy;
	long double	dz;
}	t_hail;

typedef struct s_point
{
	long double	x;
	long double	y;
	long double	z;
}	t_point;

t_point	ok_get_point(t_hail one, t_hail two)
{
	t_point		p;
	long double x1;
	long double x2;
	long double x3;
	long double x4;
	long double y1;
	long double y2;
	long double y3;
	long double y4;
	long double a;
	long double b;

	p.z = 0;
	x1 = one.x;
	x2 = one.x + one.dx;
	x3 = two.x;
	x4 = two.x + two.dx;
	y1 = one.y;
	y2 = one.y + one.dy;
	y3 = two.y;
	y4 = two.y + two.dy;
	if (one.dx == two.dx && one.dy == two.dy)
	{
		p.x = 0;
		p.y = 0;
	}
	else
	{
		a = (((x1 * y2) - (y1 * x2)) * (x3 - x4)) - ((x1 - x2) * ((x3 * y4) - (y3 * x4)));
		b = (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));
		p.x = a / b;
		a = (((x1 * y2) - (y1 * x2)) * (y3 - y4)) - ((y1 - y2) * ((x3 * y4) - (y3 * x4)));
		b = (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));
		p.y = a / b;
		if ((x2 > x1 && p.x < x1) || (x2 < x1 && p.x > x1) || (x4 > x3 && p.x < x3) || (x4 < x3 && p.x > x3))
			p.x = 0;
		if ((y2 > y1 && p.y < y1) || (y2 < y1 && p.y > y1) || (y4 > y3 && p.y < y3) || (y4 < y3 && p.y > y3))
			p.y = 0;
	}
	return (p);
}

long long	ok_findcollisions(t_hail hail[HAILS])
{
	int			i;
	int			j;
	long long	r;
	t_point		p;

	i = 0;
	r = 0;
	while (i < HAILS - 1)
	{
		j = i + 1;
		while (j < HAILS)
		{
			p = ok_get_point(hail[i], hail[j]);
			if (RA <= p.x && p.x <= RB && RA <= p.y && p.y <= RB)
			{
				hail[i].collision = 1;
				hail[j].collision = 1;
				++r;
				ft_printf("hails %i and %i collide.\n", i, j);
				printf("collision %Lfx %Lfy\n", p.x, p.y);
			}
			else
				ft_printf("hails %i and %i will not collide.\n", i, j);
			++j;
		}
		++i;
	}
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	long long	r;
	t_hail		hail[HAILS];

	j = 0;
	while (line[j])
	{
		i = 0;
		hail[j].collision = 0;
		hail[j].x = ft_latoi(&line[j][i]);
		while (line[j][i] != ' ')
			++i;
		++i;
		hail[j].y = ft_latoi(&line[j][i]);
		while (line[j][i] != ' ')
			++i;
		++i;
		hail[j].z = ft_latoi(&line[j][i]);
		while (line[j][i] != '@')
			++i;
		++i;
		++i;
		hail[j].dx = ft_latoi(&line[j][i]);
		while (line[j][i] != ' ')
			++i;
		++i;
		hail[j].dy = ft_latoi(&line[j][i]);
		while (line[j][i] != ' ')
			++i;
		++i;
		hail[j].dz = ft_latoi(&line[j][i]);
		++j;
	}
	r = ok_findcollisions(hail);
	//r = 0;
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
	line = ft_readfile(INPUT, 65536);
	//lines = ft_split(line[0], '');
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	//ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}

//24964 too high
//19093 too high
//18093 too low

// 700606076917251 too high
// 598005970525206 too high
// 587909564822811 too high
// 557789988450159 correct
// a= 201, b = 202, c = 79

//x0 = 149412455352770
//y0 = 174964385672289
//z0 = 233413147425100