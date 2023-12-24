/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p24b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/24 13:47:00 by okraus           ###   ########.fr       */
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

// t_point	ok_get_point(t_hail one, t_hail two)
// {
// 	t_point		p;
// 	long double x1;
// 	long double x2;
// 	long double x3;
// 	long double x4;
// 	long double y1;
// 	long double y2;
// 	long double y3;
// 	long double y4;
// 	long double a;
// 	long double b;

// 	p.z = 0;
// 	x1 = one.x;
// 	x2 = one.x + one.dx;
// 	x3 = two.x;
// 	x4 = two.x + two.dx;
// 	y1 = one.y;
// 	y2 = one.y + one.dy;
// 	y3 = two.y;
// 	y4 = two.y + two.dy;
// 	if (one.dx == two.dx && one.dy == two.dy)
// 	{
// 		p.x = 0;
// 		p.y = 0;
// 	}
// 	else
// 	{
// 		a = (((x1 * y2) - (y1 * x2)) * (x3 - x4)) - ((x1 - x2) * ((x3 * y4) - (y3 * x4)));
// 		b = (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));
// 		p.x = a / b;
// 		a = (((x1 * y2) - (y1 * x2)) * (y3 - y4)) - ((y1 - y2) * ((x3 * y4) - (y3 * x4)));
// 		b = (((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)));
// 		p.y = a / b;
// 		if ((x2 > x1 && p.x < x1) || (x2 < x1 && p.x > x1) || (x4 > x3 && p.x < x3) || (x4 < x3 && p.x > x3))
// 			p.x = 0;
// 		if ((y2 > y1 && p.y < y1) || (y2 < y1 && p.y > y1) || (y4 > y3 && p.y < y3) || (y4 < y3 && p.y > y3))
// 			p.y = 0;
// 	}
// 	return (p);
// }

int	ft_is_prime2(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	if (nb == 2)
		return (1);
	while (i < 28710786)
	{
		if (i < nb && (nb % i) != 0)
			i++;
		else
		{
			if (i == nb && (nb % i) == 0)
				return (1);
			else
				return (0);
		}
	}
	return (1);
}

int	ft_find_next_prime(int nb)
{
	if (nb < 3)
		return (2);
	while (ft_is_prime2(nb) == 0)
		nb++;
	return (nb);
}

void	ok_print_primes(long long d, long long s)
{
	long long	p;

	p = 2;
	while (p < 1000)
	{
		if (!(d % p))
			ft_printf("%lli ", p);
		++p;
		//p = (long long)ft_find_next_prime((int)p);
	}
	(void)s;
	ft_printf("\n");
}

void	ok_print_primes2(long long d, long long s)
{
	long long	p;
	int			r;
	int			x;

	p = 2;
	r = 79;
	x = 0;
	while (p < 1000)
	{
		if (!(d % p))
		{
			ft_printf("%lli ", s + p);
			if ((int)(s + p) == r)
				x = 1;
		}
		++p;
		// p = (long long)ft_find_next_prime((int)p)
	}
	ft_printf("\n");
	if (!x)
		ft_printf("\n\n\n79 is not the speed\n\n\n");
}

void	ok_print_primes3(long long d, long long s)
{
	long long	p;

	p = 2;
	if (s < 0)
		s *= -1;
	while (p < 1000)
	{
		if (!(d % p))
			ft_printf("%lli ", s + p);
		++p;
		// p = (long long)ft_find_next_prime((int)p);
	}
	ft_printf("\n");
}

void	ok_findsamespeed(t_hail hail[HAILS])
{
	int			i;
	int			j;
	long long	d;
	long long	s;

	i = 0;
	while (i < HAILS - 1)
	{
		j = i + 1;
		while (j < HAILS)
		{
			// if (hail[i].dx == hail[j].dx)
			// {
			// 	printf("%3i has the same x speed as %3i, x speed = %3Lf\n", i, j, hail[i].dx);
			// 	d = hail[i].x - hail[j].x;
			// 	s = hail[i].dx;
			// 	if (d < 0)
			// 		d = 0 - d;
			// 	printf("%3i distance %3i, x distance = %10Li\n", i, j, (long long)(hail[i].x - hail[j].x));
			// 	//ok_print_primes(d, s);
			// 	ok_print_primes2(d, s);
			// 	//ok_print_primes3(d, s);
			// }
			if (hail[i].dy == hail[j].dy)
			{
				printf("%3i has the same y speed as %3i, y speed = %3Lf\n", i, j, hail[i].dy);
				d = hail[i].y - hail[j].y;
				s = hail[i].dy;
				if (d < 0)
					d = 0 - d;
				printf("%3i distance %3i, y distance = %10Li\n", i, j, (long long)(hail[i].y - hail[j].y));
				//ok_print_primes(d, s);
				ok_print_primes2(d, s);
				//ok_print_primes3(d, s);
			}
			// if (hail[i].dz == hail[j].dz)
			// {
			// 	printf("%3i has the same z speed as %3i, z speed = %3Lf\n", i, j, hail[i].dz);
			// 	d = hail[i].z - hail[j].z;
			// 	s = hail[i].dz;
			// 	if (d < 0)
			// 		d = 0 - d;
			// 	printf("%3i distance %3i, z distance = %10Li\n", i, j, (long long)(hail[i].z - hail[j].z));
			// 	//ok_print_primes(d, s);
			// 	ok_print_primes2(d, s);
			// 	//ok_print_primes3(d, s);
			// }
			++j;
		}
		++i;
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
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
		printf("hail %3i, x %Lf, y %Lf, z %Lf, dx %Lf, dy %Lf, dz %Lf\n", j, hail[j].x, hail[j].y, hail[j].z, hail[j].dx, hail[j].dy, hail[j].dz);
		++j;
	}
	ok_findsamespeed(hail);
	r = 0;
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
	//ok_update(line, &total[0], i, j);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	ft_free_split(&line);
	return (0);
}

//24964 too high
//19093 too high
//18093 too low