/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p5.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 07:29:57 by okraus            #+#    #+#             */
/*   Updated: 2023/12/05 09:13:37 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_map
{
	long	s;
	long	v1[50];
	long	v2[50];
	long	v3[50];
	long	start[50];
	long	end[50];
	long	shift[50];
}					t_map;



void	ok_update2(char **line, int *ptot, int i, int j)
{
	static long	seed[8][1024];
	int	sn;
	t_map	m[7];
	int		mn;
	int		k;

	sn = 0;
	i = 0;
	j = 0;
	k = 0;
	mn = -1;
	while (line[0][i])
	{
		while (line[0][i] && !ft_isdigit(line[0][i]))
			++i;
		if (line[0][i])
		{
			seed[k][sn] = (unsigned long)ft_latoi(&line[0][i]);
			if (sn & 1)
				seed[k][sn] += seed[k][sn - 1] - 1;
			++sn;
		}
		while (ft_isdigit(line[0][i]))
			++i;
	}
	while (j < sn)
	{
		ft_printf("seed%2i = %li\n", j, seed[k][j]);
		++j;
	}
	j = 1;
	while (line[j])
	{
		i = 0;
		while (line[j][i] && !ft_isdigit(line[j][i]) && line[j][i] != 'm')
			++i;
		if (line[j][i] == 'm')
		{
			++mn;
			m[mn].s = 0;
			ft_printf("map: %i\n", mn);
		}
		else if (line[j][i])
		{
			m[mn].v1[m[mn].s] = ft_latoi(&line[j][i]);
			while (ft_isdigit(line[j][i]))
				++i;
			++i;
			m[mn].v2[m[mn].s] = ft_latoi(&line[j][i]);
			while (ft_isdigit(line[j][i]))
				++i;
			++i;
			m[mn].v3[m[mn].s] = ft_latoi(&line[j][i]);
			while (ft_isdigit(line[j][i]))
				++i;
			m[mn].start[m[mn].s] = m[mn].v2[m[mn].s];
			m[mn].end[m[mn].s] = m[mn].start[m[mn].s] + m[mn].v3[m[mn].s] - 1;
			m[mn].shift[m[mn].s] = m[mn].v1[m[mn].s] - m[mn].v2[m[mn].s];
			ft_printf("%2li %10li %10li %10li %10li %10li %11li\n", m[mn].s, m[mn].v1[m[mn].s], m[mn].v2[m[mn].s], m[mn].v3[m[mn].s], m[mn].start[m[mn].s], m[mn].end[m[mn].s], m[mn].shift[m[mn].s]);
			m[mn].s++;
		}
		++j;
	}
	i = 0;
	j = 0;
	k = 0;
	while (k < 7)
	{
		j = 0;
		while (j < m[k].s)
		{
			i = 0;
			while (i < sn)
			{
				if (i > 1000)
					exit(1);
				ft_printf("%i %i %i %i\n", i, j, k, sn);
				//ft_printf("m[k].start[j] = %li, m[k].end[j] = %li\n", m[k].start[j], m[k].end[j]);
				//ft_printf("seed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
				if (seed[k][i] >= m[k].start[j] && seed[k][i + 1] <= m[k].end[j])
				{
					seed[k + 1][i] = seed[k][i] + m[k].shift[j];
					seed[k + 1][i + 1] = seed[k][i + 1] + m[k].shift[j];
					ft_printf("found seeds in map\n");
					ft_printf("m[k].start[j] = %li, m[k].end[j] = %li\n", m[k].start[j], m[k].end[j]);
					ft_printf("seed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
				}
				else if ((seed[k][i] < m[k].start[j] && seed[k][i + 1] >= m[k].start[j])
					|| (seed[k][i] <= m[k].end[j] && seed[k][i + 1] > m[k].end[j]))
				{
					if (seed[k][i] < m[k].start[j])
					{
						ft_printf("Original1\nseed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
						seed[k][sn] = m[k].start[j];
						seed[k][sn + 1] = seed[k][i + 1];
						seed[k][i + 1] = m[k].start[j] - 1;
						ft_printf("m[k].start[j] = %li, m[k].end[j] = %li\n", m[k].start[j], m[k].end[j]);
						ft_printf("seed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
						ft_printf("seed[k][sn] = %li, seed[k][sn + 1] = %li\n", seed[k][sn], seed[k][sn + 1]);
						sn += 2;
					}
					if (seed[k][i + 1] > m[k].end[j])
					{
						ft_printf("Original2\nseed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
						seed[k][sn] = m[k].end[j] + 1;
						seed[k][sn + 1] = seed[k][i + 1];
						seed[k][i + 1] = m[k].end[j];
						ft_printf("m[k].start[j] = %li, m[k].end[j] = %li\n", m[k].start[j], m[k].end[j]);
						ft_printf("seed[k][i] = %li, seed[k][i + 1] = %li\n", seed[k][i], seed[k][i + 1]);
						ft_printf("seed[k][sn] = %li, seed[k][sn + 1] = %li\n", seed[k][sn], seed[k][sn + 1]);
						sn += 2;
					}
					j = 0;
					break ;
				}
				else if (!seed[k + 1][i] || !seed[k + 1][i + 1])
				{
					seed[k + 1][i] = seed[k][i];
					seed[k + 1][i + 1] = seed[k][i + 1];
				}
				i += 2;
			}
			++j;
		}
		++k;
	}
	i = 0;
	*ptot = 2147483647;
	while (seed[7][i])
	{
		if (seed[7][i] < (long)*ptot)
			*ptot = seed[7][i];
		++i;
	}
}

int	main(void)
{
	int 	fd;
	char	*line[300];
	int		i;
	int		j;
	int		total[2];

	i = 0;
	j = 0;
	fd = open("input", O_RDONLY);
	line[0] = 0;
	line[j] = get_next_line(fd);
	total[0] = 0;
	total[1] = 0;
	while (line[j])
	{
		i = ft_strlen(line[j]);
		//ft_printf("i = %i\n", i);
		// ok_update(line, &total[0], i, j);
		// ft_printf("t1=%5d\n", total[0]);
		// ok_update2(line, &total[1], i, j);
		// ft_printf("t2=%5d\n", total[1]);
		//free(line);
		++j;
		line[j] = get_next_line(fd);		
	}
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	//ok_update(line, &total[0], i, j);
	//ft_printf("t1=%5d\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5d\n", total[1]);
	close(fd);
	return (0);
}
