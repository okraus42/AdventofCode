/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p14.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/14 07:22:44 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ok_swap(char *c1, char *c2)
{
	if (*c1 == '.' && *c2 == 'O')
	{
		*c1 = 'O';
		*c2 = '.';
		return (1);
	}
	return (0);
}

int	ok_sort(char **line)
{
	int	i;
	int	j;
	int	max;
	int	s;

	j = 0;
	while (line[j])
		++j;
	max = j;
	j = 0;
	s = 1;
	while (s)
	{
		s = 0;
		j = 0;
		while (j < max - 1)
		{
			i = 0;
			while (line[j][i])
			{
				s += ok_swap(&line[j][i], &line[j + 1][i]);
				++i;
			}
			++j;
		}
	}
	return (max);
}

int	ok_countboulders(char *str, int score)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i])
	{
		if (str[i] == 'O')
			r += score;
		++i;
	}
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int	score;

	j = 0;
	score = ok_sort(line);
	while (line[j])
	{
		*ptot += ok_countboulders(line[j], score);
		--score;
		++j;
	}
	(void)i;
}


int	ok_sort2(char **line)
{
	int	i;
	int	j;
	int	max;
	int	end;
	int	s;

	j = 0;
	end = 0;
	while (line[0][end])
		++end;
	while (line[j])
		++j;
	max = j;
	j = 0;
	s = 1;
	while (s)
	{
		s = 0;
		j = 0;
		while (j < max - 1)
		{
			i = 0;
			while (line[j][i])
			{
				s += ok_swap(&line[j][i], &line[j + 1][i]);
				++i;
			}
			++j;
		}
	}
	s = 1;
	while (s)
	{
		s = 0;
		j = 0;
		while (j < max)
		{
			i = 0;
			while (line[j][i + 1])
			{
				s += ok_swap(&line[j][i], &line[j][i + 1]);
				++i;
			}
			++j;
		}
	}
	s = 1;
	while (s)
	{
		s = 0;
		j = max - 2;
		while (j >= 0)
		{
			i = 0;
			while (line[j][i])
			{
				s += ok_swap(&line[j + 1][i], &line[j][i]);
				++i;
			}
			--j;
		}
	}
	s = 1;
	while (s)
	{
		s = 0;
		j = 0;
		while (j < max)
		{
			i = end;
			while (i >= 0)
			{
				s += ok_swap(&line[j][i + 1], &line[j][i]);
				--i;
			}
			++j;
		}
	}
	return (max);
}


void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int	score;
	int	sum;
	int	cycle;

	j = 0;
	cycle = 0;
	while (cycle < 1000)
	{
		score = ok_sort2(line);
		sum = 0;
		j = 0;
		while (line[j])
		{
			sum += ok_countboulders(line[j], score);
			--score;
			++j;
		}
		//ft_printf("%i   ", sum);

		//magic need to recode and spot the length of repeating sequence it might not always be 7
		if (cycle > 100 && ((cycle + 1) % 7) == 1000000000 % 7)
			ft_printf("%i\n", sum);
		++cycle;
	}
	j = 0;
	sum = 0;
	score = ok_sort2(line);
	while (line[j])
	{
		sum += ok_countboulders(line[j], score);
		--score;
		++j;
	}
	*ptot = sum;
	(void)i;
}

int	main(void)
{
	char		**line;
	int			i;
	int			j;
	long long	total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
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
