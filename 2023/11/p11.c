

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p11.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/11 14:55:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ok_calc_distance(int oi, int oj, int i, int j, int lines[20], int columns[20])
{
	int	extraline;
	int	extracolumn;
	int	ld;
	int	cd;
	int	c;

	c = 0;
	extraline = 0;
	extracolumn = 0;
	while (lines[c])
	{
		if ((oj < lines[c] && j > lines[c]) || (j < lines[c] && oj > lines[c]))
			++extraline;
		++c;
	}
	c = 0;
	while (columns[c])
	{
		if ((oi < columns[c] && i > columns[c]) || (i < columns[c] && oi > columns[c]))
			++extracolumn;
		++c;
	}
	if (i > oi)
		ld = i - oi;
	else
		ld = oi - i;
	if (j > oj)
		cd = j - oj;
	else
		cd = oj - j;
	//ft_printf("oi %i oj %i \n", oi, oj);
	//ft_printf("return %i + %i + %i + %i = %i\n", cd, ld, extraline, extracolumn, cd + ld + extraline + extracolumn);
	return (cd + ld + extraline + extracolumn);
}

void	ok_adddistances(char **line, long long *ptot, int j, int i, int lines[20], int columns[20])
{
	int oi;
	int	oj;

	oi = i;
	oj = j;
	++i;
	while (line[j][i])
	{
			if (line[j][i] == '#')
				*ptot += ok_calc_distance(oi, oj, i, j, lines, columns);
			++i;
	}
	++j;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				*ptot += ok_calc_distance(oi, oj, i, j, lines, columns);
			++i;
		}
		++j;
	}
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int lines[20];
	int	columns[20];
	int	r;
	int cl;
	int	cc;
	
	j = 0;
	cl = 0;
	while (line[j])
	{
		i = 0;
		r = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				++r;
			++i;
		}
		if (!r)
		{
			lines[cl] = j;
			++cl;
		}
		++j;
	}
	lines[cl] = 0;
	j = 0;
	i = 0;
	cc = 0;
	//ft_printf("cc = %i, cl = %i\n", cc, cl);
	while (line[j][i])
	{
		r = 0;
		//ft_printf("i %i\n", i);
		while (line[j])
		{
			//ft_printf("j %i\n", j);
			if (line[j][i] == '#')
				++r;
			++j;
		}
		if (!r)
		{
			columns[cc] = i;
			++cc;
		}
		j = 0;
		++i;
	}
	columns[cc] = 0;
	ft_printf("cc = %i, cl = %i\n", cc, cl);
	i = 0;
	while (lines[i])
	{
		ft_printf("line %i\n", lines[i]);
		++i;
	}
	i = 0;
	while (columns[i])
	{
		ft_printf("column %i\n", columns[i]);
		++i;
	}
	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				ok_adddistances(line, ptot, j, i, lines, columns);
			++i;
		}
		++j;
	}
}


int	ok_calc_distance2(int oi, int oj, int i, int j, int lines[20], int columns[20])
{
	int	extraline;
	int	extracolumn;
	int	ld;
	int	cd;
	int	c;

	c = 0;
	extraline = 0;
	extracolumn = 0;
	while (lines[c])
	{
		if ((oj < lines[c] && j > lines[c]) || (j < lines[c] && oj > lines[c]))
			extraline += 999999;
		++c;
	}
	c = 0;
	while (columns[c])
	{
		if ((oi < columns[c] && i > columns[c]) || (i < columns[c] && oi > columns[c]))
			extracolumn += 999999;
		++c;
	}
	if (i > oi)
		ld = i - oi;
	else
		ld = oi - i;
	if (j > oj)
		cd = j - oj;
	else
		cd = oj - j;
	//ft_printf("oi %i oj %i \n", oi, oj);
	//ft_printf("return %i + %i + %i + %i = %i\n", cd, ld, extraline, extracolumn, cd + ld + extraline + extracolumn);
	return (cd + ld + extraline + extracolumn);
}

void	ok_adddistances2(char **line, long long *ptot, int j, int i, int lines[20], int columns[20])
{
	int oi;
	int	oj;

	oi = i;
	oj = j;
	++i;
	while (line[j][i])
	{
			if (line[j][i] == '#')
				*ptot += ok_calc_distance2(oi, oj, i, j, lines, columns);
			++i;
	}
	++j;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				*ptot += ok_calc_distance2(oi, oj, i, j, lines, columns);
			++i;
		}
		++j;
	}
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int lines[20];
	int	columns[20];
	int	r;
	int cl;
	int	cc;
	
	j = 0;
	cl = 0;
	while (line[j])
	{
		i = 0;
		r = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				++r;
			++i;
		}
		if (!r)
		{
			lines[cl] = j;
			++cl;
		}
		++j;
	}
	lines[cl] = 0;
	j = 0;
	i = 0;
	cc = 0;
	//ft_printf("cc = %i, cl = %i\n", cc, cl);
	while (line[j][i])
	{
		r = 0;
		//ft_printf("i %i\n", i);
		while (line[j])
		{
			//ft_printf("j %i\n", j);
			if (line[j][i] == '#')
				++r;
			++j;
		}
		if (!r)
		{
			columns[cc] = i;
			++cc;
		}
		j = 0;
		++i;
	}
	columns[cc] = 0;
	//ft_printf("cc = %i, cl = %i\n", cc, cl);
	i = 0;
	while (lines[i])
	{
		//ft_printf("line %i\n", lines[i]);
		++i;
	}
	i = 0;
	while (columns[i])
	{
		//ft_printf("column %i\n", columns[i]);
		++i;
	}
	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (line[j][i] == '#')
				ok_adddistances2(line, ptot, j, i, lines, columns);
			++i;
		}
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
