/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p13.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/13 11:04:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ok_columns(char **line, int s, int end, int max, int i)
{
	int	j;
	int	k;

	j = s;
	k = i + 1;
	//ft_printf("%.*CCstart%C\n", 0xFFFF00);
	while (i >= 0 && k < end)
	{
		j = s;
		while (j < max)
		{
			//ft_printf("Ci %i j %i k %i %c %c\n", i, j, k, line[j][i], line[j][k]);
			if (line[j][i] != line[j][k])
				return (0);
			++j;
		}
		--i;
		++k;
	}
	//ft_printf("%.*CCreturn%C\n", 0xFFFF00);
	return (1);
}

int	ok_rows(char **line, int s, int end, int max, int j)
{
	int	i;
	int	k;

	i = 0;
	k = j + 1;
	ft_printf("%.*CRstart%C\n", 0xFFFF00);
	while (j >=s && k < max)
	{
		i = 0;
		while (i < end)
		{
			ft_printf("Ri %i j %i k %i %c %c\n", i, j, k, line[j][i], line[k][i]);
			if (line[j][i] != line[k][i])
				return (0);
			++i;
		}
		--j;
		++k;
	}
	ft_printf("%.*CRreturn%C\n", 0xFFFF00);
	return (1);
}

int	ok_checkmirrors(char **line, int *start, int *fresults)
{
	int	i;
	int	j;
	int	end;
	int s;
	int	max;
	int	result;

	end = 0;
	while (line[*start][end])
		++end;
	max = *start;
	s = *start;
	j = s;
	while (line[max] && line[max][0] && line[max][0] != '0')
		++max;
	*start = max;
	result = 0;
	i = 0;
	while (i < end - 1)
	{
		if (ok_columns(line, s, end, max, i))
			result += i + 1;
		++i;
	}
	while (j < max - 1)
	{
		if (ok_rows(line, s, end, max, j))
			result += (j - s + 1) * 100;
		++j;
	}
	ft_printf("%5i %5i\n", s, result);
	fresults[s] = result;
	return (result);
}

void	ok_update(char **line, long long *ptot, int i, int j, int *fresults)
{

	j = 0;
	while (line[j])
	{
		if (line[j][0] && line[j][0] != '0')
			*ptot += ok_checkmirrors(line, &j, fresults);
		else
			++j;
	}
	(void)i;
}

void	ok_swap(char *c)
{
	if (*c == '.')
		*c = '#';
	else if (*c == '#')
		*c = '.';
}

int	ok_checkmirrors2(char **line, int *start, int *fresults)
{
	int	i;
	int	j;
	int	end;
	int s;
	int	max;
	int	result;
	int	ii;
	int	jj;

	end = 0;
	while (line[*start][end])
		++end;
	max = *start;
	s = *start;
	j = s;
	while (line[max] && line[max][0] && line[max][0] != '0')
		++max;
	*start = max;
	result = 0;
	i = 0;
	
	jj = s;
	while (jj < max && (!result || result == fresults[s]))
	{
		ii = 0;
		while (ii < end && (!result || result == fresults[s]))
		{
			ok_swap(&line[jj][ii]);
			i = 0;
			while (i < end - 1 && (!result || result == fresults[s]))
			{
				if (ok_columns(line, s, end, max, i))
					result = i + 1;
				++i;
			}
			j = s;
			while (j < max - 1 && (!result || result == fresults[s]))
			{
				if (ok_rows(line, s, end, max, j))
					result = (j - s + 1) * 100;
				++j;
			}
			ok_swap(&line[jj][ii]);
			++ii;
	}
		++jj;
	}
	ft_printf("%5i %5i\n", s, result);
	return (result);
}

void	ok_update2(char **line, long long *ptot, int i, int j, int *fresults)
{

	j = 0;
	while (line[j])
	{
		if (line[j][0] && line[j][0] != '0')
			*ptot += ok_checkmirrors2(line, &j, fresults);
		else
			++j;
	}
	(void)i;
}

int	main(void)
{
	char		**line;
	int			i;
	int			j;
	long long	total[2];
	int			fresults[1500];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
	//ft_printf("%p\n", (void *)line);
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j, fresults);
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j, fresults);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
