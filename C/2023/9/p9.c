/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p9.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/09 14:55:25 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
int	arr[22][22];

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

void	ok_resetarr(void)
{
	int	i;
	int	j;

	j = 0;
	while (j < 22)
	{
		i = 0;
		while (i < 22)
		{
			arr[j][i] = 0;
			++i;
		}
		++j;
	}
}

void	ok_setarr(int *arr, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 21)
	{
		arr[j] = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]) || str[i] == '-')
			++i;
		++i;
		++j;
	}
	j = 0;
	while (j < 21)
	{
		ft_printf("%i ", arr[j]);
		++j;
	}
	ft_printf("\n");
}

void	ok_calcarr(void)
{
	int	i;
	int	j;

	j = 0;
	while (arr[j][0] || arr[j][1] || arr[j][2] || arr[j][3] || arr[j][4] || arr[j][5] || arr[j][6] || arr[j][7] || arr[j][8] || arr[j][9]
		|| arr[j][10] || arr[j][11] || arr[j][12] || arr[j][13] || arr[j][14] || arr[j][15] || arr[j][16] || arr[j][17] || arr[j][18] || arr[j][19])
	{
		i = 0;
		while (i < 21 - j - 1)
		{
			arr[j + 1][i] = arr[j][i + 1] - arr[j][i];
			ft_printf("%.255C%i %C", arr[j + 1][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
	//++i;
	while (j >= 0)
	{
		ft_printf("%i %i %i\n", arr[j][i], j, i);
		ft_printf("%i %i %i\n", arr[j][i - 1], j, i);
		arr[j][i] = arr[j][i - 1] + arr[j + 1][i - 1];
		ft_printf("%i %i\n", arr[j][i - 1], arr[j - 1][i - 1]);
		ft_printf("%i %i %i\n", arr[j][i], j, i);
		++i;
		--j;
	}
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	i = 0;
	j = 0;
	while (line[j])
	{
		ok_resetarr();
		ok_setarr(arr[0], line[j]);
		ok_calcarr();
		*ptot += arr[0][21];
		++j;
	}
	(void)i;
}

void	ok_calcarr2(void)
{
	int	i;
	int	j;
	int a[22];

	j = 0;
	while (arr[j][0] || arr[j][1] || arr[j][2] || arr[j][3] || arr[j][4] || arr[j][5] || arr[j][6] || arr[j][7] || arr[j][8] || arr[j][9]
		|| arr[j][10] || arr[j][11] || arr[j][12] || arr[j][13] || arr[j][14] || arr[j][15] || arr[j][16] || arr[j][17] || arr[j][18] || arr[j][19])
	{
		i = 0;
		while (i < 21 - j - 1)
		{
			arr[j + 1][i] = arr[j][i + 1] - arr[j][i];
			ft_printf("%.255C%i %C", arr[j + 1][i]);
			++i;
		}
		ft_printf("\n");
		++j;
	}
	//++i;
	a[j] = 0;
	a[j + 1] = 0;
 	while (j >= 0)
	{
		a[j] = arr[j][0] - a[j + 1];
		ft_printf("%i %i\n", arr[j][0], a[j + 1]);
		ft_printf("%i %i\n", a[j], j);

		--j;
	}
	arr[0][21] = a[0];
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	i = 0;
	j = 0;
	while (line[j])
	{
		ok_resetarr();
		ok_setarr(arr[0], line[j]);
		ok_calcarr2();
		*ptot += arr[0][21];
		++j;
	}
	(void)i;
}
// void	ok_update2(char **line, long long *ptot, int i, int j)
// {
	
// }

int	main(void)
{
	char	**line;
	int		i;
	int		j;
	long long		total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
	ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5d\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
