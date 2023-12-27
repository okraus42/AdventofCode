/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p12e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/27 16:40:13 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

#define ITERS 1
#define INPUT "test2"

typedef struct	s_content
{
	char	s[500];
	int		i;
}	t_content;


void	ok_getnumbers(char *str, int numbers[100], int i, int *qm)
{
	int	k;

	k = 0;
	i = 0;
	*qm = 0;
	while (str[i])
	{
		if (str[i] == '?')
			*qm += 1;
		if (str[i] == ' ')
		{
			++i;
			while (str[i])
			{
				numbers[k] = ft_atoi(&str[i]);
				++k;
				while (ft_isdigit(str[i]))
					++i;
				if (str[i])
					++i;
			}
			break ;
		}
		if (str[i])
			++i;
	}
	while (k < 100)
		numbers[k++] = 0;
}


void	ok_strcpyspace(char* s2, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		s2[i] = str[i];
		++i;
	}
	s2[i] = 0;
	s2[i + 1] = 0;
	s2[i + 2] = 0;
}

void	ok_tests2(char *s2, long long p, int qm, int check[100])
{
	int	i;
	int	t;
	long long	b;

	i = 0;
	t = 0;

	while (s2[i] && t < qm)
	{
		b = 1;
		if (s2[i] == '?')
		{
			b <<= t;
			if (p & b)
				s2[i] = '.';
			else
				s2[i] = '#';
			++t;
		}
		++i;
	}
	i = 0;
	t = 0;
	b = 0;
	while (s2[i])
	{
		if (s2[i] == '#')
			++t;
		else if (i > 0 && s2[i - 1] == '#')
		{
			check[b] = t;
			t = 0;
			++b;
		}
		++i;
	}
	if (t)
	{
		check[b] = t;
		check[b + 1] = 0;
	}
	else	
		check[b] = 0;
}

int	ok_checknum(int numbers[100], int check[100])
{
	int	i;

	i = 0;
	while (numbers[i])
	{
		if (numbers[i] != check[i])
			return (0);
		++i;
	}
	if (!check[i])
		return (1);
	return (0);
}

int	ok_checknumbers(char *str, int numbers[100], int check[100], int qm)
{
	int		r;
	long long	p;
	//int		k;
	long long		max;
	char	s2[500];

	ok_strcpyspace(s2, str);
	//ft_printf("s2: %s\n", s2);
	max = 1;
	max <<= qm;
	//ft_printf("max = %i\n", max);
	p = 0;
	r = 0;
	while (p < max)
	{
		ok_tests2(s2, p, qm, check);
		// ft_printf("%i s2: %s\n", p, s2);
		// k = 0;
		// while (check[k])
		// {
		// 	ft_printf("n[%i]: %2i, ", k, check[k]);
		// 	++k;
		// }
		// ft_printf("\n");
		if (ok_checknum(numbers, check))
			++r;
		++p;
		ok_strcpyspace(s2, str);
	}
	ft_printf ("r %i\n", r);
	return (r);
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	int	numbers[100];
	int	check[100];
	int	qm;

	j = 0;
	while (line[j])
	{
		qm = 0;
		ok_getnumbers(line[j], numbers, i, &qm);
		//ft_printf("%s\n", line[j]);
		//ft_printf("qm: %2i | ", qm);
		// while (numbers[k])
		// {
		// 	//ft_printf("n[%i]: %2i, ", k, numbers[k]);
		// 	++k;
		// }
		//ft_printf("\n");
		*ptot += ok_checknumbers(line[j], numbers, check, qm);
		++j;
	}
}

void	ok_getnewline(char *newline, char *line)
{
	int	i;
	int	j;
	int	start2;
	int	iter;
	int	iters;

	i = 0;
	j = 0;
	iter = 0;
	iters = ITERS;
	while (iter < iters)
	{
		i = 0;
		while (line[i] != ' ')
		{
			newline[j] = line[i];
			++i;
			++j;
		}
		++iter;
		if (iter < iters)
		{
			newline[j] = '?';
			++j;
		}
	}
	newline[j] = line[i];
	++j;
	++i;
	start2 = i;
	iter = 0;
	while (iter < iters)
	{
		i = start2;
		while (line[i])
		{
			newline[j] = line[i];
			++i;
			++j;
		}
		++iter;
		if (iter < iters)
		{
			newline[j] = ',';
			++j;
		}
	}
	newline[j] = 0;
}

void	ok_strcpyspace2(char *str, char *s)
{
	int		i;
	//char	*s;

	// i = 0;
	// while (str[i] && str[i] != ' ')
	// 	++i;
	// s = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		s[i] = str[i];
		++i;
	}
	s[i] = '.';
	s[i + 1] = 0;
	s[i + 2] = 0;
	//return (s);
}

void	ok_checknumbers2(char str[500], int numbers[100], int s, int num, long long array[100][500])
{
	long long	r;
	int			n;
	int			i;
	int			h;

	//ft_printf("s %s, i %i, num[%i] %i\n", str, s, num, numbers[num]);
	if (array[num][s] != -1)
		return ;
	if (num && !numbers[num - 1])
	{
		array[num][s] = 0;
		return ;
	}
	// parse . and #
	i = s;
	n = num;
	r = 0;
	while (str[i])
	{
		ft_printf("1analysing: %s\n", &str[i]);
		if (str[i] == '?')
		{
			break ;
		}
		else if (str[i] == '.')
		{
			++i;
		}
		else if (str[i] == '#')
		{
			h = numbers[n];
			while (h)
			{
				if (!str[i] && h)
				{
					array[num][s] = 0;
					return ;
				}
				if (str[i] == '.' && h)
				{
					array[num][s] = 0;
					return ;
				}
				--h;
				++i;
			}
			n++;
			if (str[i] == '#')
			{
				array[num][s] = 0;
				return ;
			}
			if (!str[i])
				break ;
		}
		ft_printf("2analysing: %s\n", &str[i]);
	}
	if (str[i] == '?')
	{
		ft_printf("ANALYSING: %s %i\n", &str[i], numbers[n]);
		ok_checknumbers2(str, numbers, i + 1, n, array);
		r += array[n][i + 1];
		ft_printf(".array[%i][%i] = %lli, str %s, num %i\n", n, i + 1, array[n][i + 1], &str[i + 1], numbers[n]);
		h = numbers[n];
		while (h)
		{
			if (!str[i] && h)
			{
				array[num][s] = r;
				return ;
			}
			if (str[i] == '.' && h)
			{
				array[num][s] = r;
				return ;
			}
			--h;
			++i;
		}
		n++;
		if (str[i] == '#')
		{
			array[num][s] = r;
			return ;
		}
		if (str[i])
		{
			ok_checknumbers2(str, numbers, i + 1, n, array);
			r += array[n][i + 1];
			ft_printf("#array[%i][%i] = %lli, str %s, num %i\n", n, i + 1, array[n][i + 1], &str[i + 1], numbers[n]);
		}
	}
	if (!str[i] && !numbers[n] && numbers[n - 1])
		array[num][s] = 1;
	else
		array[num][s] = r; 
	ft_printf("array[%i][%i] = %lli, str %s\n", num, s, array[num][s], &str[s]);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int			numbers[100];
	//int			check[100];
	char		newline[500];
	long long	array[100][500];
	char		s[500];
	int			qm;
	long long	t;
	int			x;
	int			y;
	//int		c;

	j = 0;
	//memo;
	//c = 0;
	while (line[j])
	{
		//qm = 0;
		//ok_getnumbers(line[j], numbers, i, &qm);
		//t[0] = ok_checknumbers(line[j], numbers, check, qm);
		ok_getnewline(newline, line[j]);
		ft_printf("newline[%i]: %s\n", j, newline);
		qm = 0;
		ok_getnumbers(newline, numbers, i, &qm);
		//ft_printf("%s\n", newline);
		//ft_printf("qm: %2i | ", qm);
		// while (numbers[k])
		// {
		// 	//ft_printf("n[%i]: %2i, ", k, numbers[k]);
		// 	++k;
		// }
		//ft_printf("\n");
		ok_strcpyspace2(newline, s);
		ft_printf("newstr: %s\n", s);
		t = 0;
		y = 0;
		while (y < 100)
		{
			x = 0;
			while (x < 500)
			{
				array[y][x] = -1;
				++x;
			}
			++y;
		}
		ok_checknumbers2(s, numbers, 0, 0, array);
		// ft_printf("t[0] = %lli\n", t[0]);
		//free(s);
		//ft_printf("t[2] = %lli\n", t[2]);
		y = 0;
		t = array[0][0];
		ft_printf("array[0][0]= %i\n", array[0][0]);
		*ptot += t;
		++j;
	}
}

// void	ok_update2(char **line, long long *ptot, int i, int j)
// {
// 	int			numbers[100];
// 	//int			check[100];
// 	char		newline[500];
// 	long long	array[100][500];
// 	char		s[500];
// 	int			qm;
// 	int			y;
// 	//int		c;

// 	j = 0;
// 	//c = 0;
// 	while (line[j])
// 	{
// 		qm = 0;
// 		i = 0;
		
// 		ok_getnewline(newline, line[j]);
// 		ok_getnumbers(newline, numbers, i, &qm);
// 		ok_strcpyspace2(newline, s);
// 		while (i < 500)
// 		{
// 			y = 0;
// 			while (y < 100)
// 			{
// 				array[y][i] = -1;
// 				++y;
// 			}
// 			++i;
// 		}
// 		ft_printf("newline: %s\n", newline);
// 		//ft_printf("s %s\n", s);
// 		i = 0;
// 		while (numbers[i])
// 		{
// 			//ft_printf("%i ", numbers[i]);
// 			++i;
// 		}
// 		//ft_printf("\n");
// 		*ptot += ok_checknumbers2(s, numbers, array);

// 		//free(s);
// 		//t[2] = t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0];
// 		// if (t[1] % t[0])
// 		// 	ft_printf("CC = %2i\n", ++c);
// 		//ft_printf("t[2] = %lli\n", t[2]);
// 		++j;
// 	}
// }

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
	line = ft_readfile(INPUT, 65536);
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
