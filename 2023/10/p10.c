/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p10.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/11 14:57:30 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void	ok_setarr(int arr[140][140])
{
	int	i;
	int	j;

	j = 0;
	while (j < 140)
	{
		i = 0;
		while (i < 140)
		{
			arr[j][i] = 0;
			++i;
		}
		++j;
	}
}

void	ok_finds(char **line, int *i, int *j)
{
	*j = 0;
	while (*j < 140)
	{
		*i = 0;
		while (*i < 140)
		{
			if (line[*j][*i] == 'S')
				return ;
			++*i;
		}
		++*j;
	}
}

void	ok_floodfill(char **line, int arr[140][140], int i, int j, int r)
{
	if (!arr[j][i] || arr[j][i] > r)
	{
		arr[j][i] = r;
		if (j + 1 < 140 && (!arr[j + 1][i] || arr[j + 1][i] > r + 1) && ft_strchr("SF7|", line[j][i]) && ft_strchr("LJ|", line[j + 1][i]))
			ok_floodfill(line, arr, i, j + 1, r + 1);
		if (j - 1 >= 0 && (!arr[j - 1][i] || arr[j - 1][i] > r + 1) && ft_strchr("SLJ|", line[j][i]) && ft_strchr("7F|", line[j - 1][i]))
			ok_floodfill(line, arr, i, j - 1, r + 1);
		if (i + 1 < 140 && (!arr[j][i + 1] || arr[j][i + 1] > r + 1) && ft_strchr("S-LF", line[j][i]) && ft_strchr("7J-", line[j][i + 1]))
			ok_floodfill(line, arr, i + 1, j, r + 1);
		if (i - 1 >= 0 && (!arr[j][i - 1] || arr[j][i - 1] > r + 1) && ft_strchr("S-7J", line[j][i]) && ft_strchr("LF-", line[j][i - 1]))
			ok_floodfill(line, arr, i - 1, j, r + 1);
	}
}

int	ok_findmax(int arr[140][140])
{
	int	i;
	int	j;
	int	max;

	j = 0;
	max = 0;
	while (j < 140)
	{
		i = 0;
		while (i < 140)
		{
			if (arr[j][i] > max)
				max = arr[j][i];
			++i;
		}
		++j;
	}
	return (max);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int arr[140][140];
	
	i = 0;
	j = 0;
	ok_setarr(arr);
	ok_finds(line, &i, &j);
	//ft_printf("j = %i, i = %i\n", j, i);
	ok_floodfill(line, arr, i, j, 0);
	*ptot = ok_findmax(arr);
}

void	ok_setarr2(int arr[279][279])
{
	int	i;
	int	j;

	j = 0;
	while (j < 279)
	{
		i = 0;
		while (i < 279)
		{
			arr[j][i] = 0;
			++i;
		}
		++j;
	}
}

void	ok_setline2(char **line, char line2[279][279])
{
	int	i;
	int	j;

	j = 0;
	while (j < 279)
	{
		i = 0;
		while (i < 279)
		{
			if (!(i % 2) && !(j % 2))
				line2[j][i] = line[j / 2][i / 2];
			else
				line2[j][i] = '?';
			++i;
		}
		++j;
	}
	ft_printf("aaa\n");
	j = 0;
	while (j < 279)
	{
		i = 0;
		while (i < 279)
		{
			//ft_printf("i=%i, j = %i\n", i, j);
			if (i % 2)
			{
				if (ft_strchr("F-SL", line2[j][i - 1]) && ft_strchr("7SJ-", line2[j][i + 1]))
					line2[j][i] = '-';
			}
			else if (j % 2)
			{
				if (ft_strchr("F|7S", line2[j - 1][i]) && ft_strchr("SJL|", line2[j + 1][i]))
					line2[j][i] = '|';
			}
			++i;
		}
		++j;
	}
}

void	ok_finds2(char line2[279][279], int *i, int *j)
{
	*j = 0;
	while (*j < 279)
	{
		*i = 0;
		while (*i < 279)
		{
			if (line2[*j][*i] == 'S')
				return ;
			++*i;
		}
		++*j;
	}
}

void	ok_floodfill2(char line2[279][279], int arr2[279][279], int i, int j, int r)
{
	if (!arr2[j][i] || arr2[j][i] > r)
	{
		arr2[j][i] = r;
		if (j + 1 < 279 && (!arr2[j + 1][i] || arr2[j + 1][i] > r + 1) && ft_strchr("SF7|", line2[j][i]) && ft_strchr("LJ|", line2[j + 1][i]))
			ok_floodfill2(line2, arr2, i, j + 1, r + 1);
		if (j - 1 >= 0 && (!arr2[j - 1][i] || arr2[j - 1][i] > r + 1) && ft_strchr("SLJ|", line2[j][i]) && ft_strchr("7F|", line2[j - 1][i]))
			ok_floodfill2(line2, arr2, i, j - 1, r + 1);
		if (i + 1 < 279 && (!arr2[j][i + 1] || arr2[j][i + 1] > r + 1) && ft_strchr("S-LF", line2[j][i]) && ft_strchr("7J-", line2[j][i + 1]))
			ok_floodfill2(line2, arr2, i + 1, j, r + 1);
		if (i - 1 >= 0 && (!arr2[j][i - 1] || arr2[j][i - 1] > r + 1) && ft_strchr("S-7J", line2[j][i]) && ft_strchr("LF-", line2[j][i - 1]))
			ok_floodfill2(line2, arr2, i - 1, j, r + 1);
	}
}

void	ok_floodfill2a(char line2[279][279], int arr2[279][279], int i, int j, int r)
{
	if (!arr2[j][i] && line2[j][i] != r)
	{
		line2[j][i] = r;
		if (j + 1 < 279)
			ok_floodfill2a(line2, arr2, i, j + 1, r);
		if (j - 1 >= 0)
			ok_floodfill2a(line2, arr2, i, j - 1, r);
		if (i + 1 < 279)
			ok_floodfill2a(line2, arr2, i + 1, j, r);
		if (i - 1 >= 0)
			ok_floodfill2a(line2, arr2, i - 1, j, r);
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int 	arr2[279][279];
	char	line2[279][279];

	j = 0;
	ok_setarr2(arr2);
	ft_printf("a\n");
	ok_setline2(line, line2);
	ft_printf("b\n");
	ok_finds2(line2, &i, &j);
	ft_printf("j = %i, i = %i\n", j, i);
	ok_floodfill2(line2, arr2, i, j, 0);
	ok_floodfill2a(line2, arr2, 0, 0, 'O');
	ok_floodfill2a(line2, arr2, 0, 278, 'O');
	ok_floodfill2a(line2, arr2, 278, 0, 'O');
	ok_floodfill2a(line2, arr2, 278, 278, 'O');
	j = 0;
	while (j < 279)
	{
		i = 0;
		while (i < 279)
		{
			if (arr2[j][i])
				ft_printf("%^*C%c%C", 255, line2[j][i]);
			else if (line2[j][i] != '?' && line2[j][i] != 'O' && !(i % 2) && !(j % 2))
			{
				ft_printf("%^*C%c%C", 0xAA0000, 'I');
				*ptot += 1;
			}
			else
				ft_printf("%c", ' ');
			++i;
		}
		ft_printf("\n");
		++j;
	}
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
	ft_printf("t1=%5d\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
