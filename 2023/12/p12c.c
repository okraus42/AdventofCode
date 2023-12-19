/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p12c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/18 18:48:51 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

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
	numbers[k] = 0;
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
	iters = 1;
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

// void	ok_tests2b(char *str, int check[100])
// {
// 	int	i;
// 	int	t;
// 	int	b;

// 	i = 0;
// 	t = 0;
// 	b = 0;
// 	while (str[i])
// 	{
// 		//ft_printf("char %i = %c\n", i, str[i]);
// 		if (str[i] == '#' || str[i] == '?')
// 		{
// 			//ft_printf("++t\n");
// 			++t;
// 		}
// 		else if (i > 0 && (str[i - 1] == '#' || str[i - 1] == '?'))
// 		{
// 			//ft_printf("reset\n");
// 			check[b] = t;
// 			t = 0;
// 			++b;
// 		}
// 		//ft_printf("%i %i %i\n", i > 0, str[i - 1] == '#', i > 0 && str[i - 1] == '#');
// 		//ft_printf("%i %i %i\n", i, t, b);
// 		++i;
// 	}
// 	if (t)
// 	{
// 		check[b] = t;
// 		check[b + 1] = 0;
// 		check[b + 2] = 0;
// 	}
// 	else
// 	{
// 		check[b] = 0;
// 		check[b + 1] = 0;
// 	}
// }

// int	ok_checknum2(int numbers[100], int check[100], char *str, int i, int j, int k)
// {
// 	int	hash;


// 	ok_tests2b(str, check);
// 	//ft_printf("%.*CChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, j, k);
// 	//ft_printf("%.*CC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
// 	while (str[i] && str[i] != '?')
// 	{
// 		if (str[i] == '#')
// 		{
// 			hash = 0;
// 			if (numbers[j] > check[k])
// 			{
// 				//ft_printf("%.*Cfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 				return (0);
// 			}
// 			while (str[i] == '#')
// 			{
// 				++i;
// 				++hash;
// 			}
// 			if (numbers[j] < hash)
// 			{
// 				//ft_printf("%.*Cfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 				return (0);
// 			}
// 			if (str[i] != '?')
// 			{
// 				if (numbers[j] != check[k])
// 				{
// 					//ft_printf("%.*Cfailcheck1c %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 					return (0);
// 				}
// 				++k;
// 				++j;
// 			}
// 		}
// 		else
// 			++i;
// 	}
// 	//ft_printf("passed check 1 %s i %i j %i k %i\n", str, i, j, k);
// 	while (numbers[j])
// 	{
// 		if (!check[k] && !check[k + 1])
// 		{
// 			//ft_printf("%.*Ccheck[%i] %i%C\n", 0xFF0000, k, check[k]);
// 			//ft_printf("%.*Cfailcheck2 %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 			return (0);
// 		}
// 		if (check[k] > numbers[j])
// 		{
// 			check[k] -= (numbers[j] + 1);
// 			++j;
// 		}
// 		else if (check[k] == numbers[j])
// 		{
// 			++j;
// 			++k;
// 		}
// 		else
// 			++k;
// 	}
// 	//ft_printf("passed check 2 %s i %i j %i k %i\n", str, i, j, k);
// 	if (str[i])
// 	{
// 		//ft_printf("%.*Cpassed check 3a %s i %i j %i k %i%C\n", 0xFFFF00, str, i, j, k);
// 		return (1);
// 	}
// 	if ((!check[k] && !check[k + 1]))
// 	{
// 		//ft_printf("%.*Cpassed check 3b %s i %i j %i k %i%C\n", 0x00FFFF, str, i, j, k);
// 		return (1);
// 	}
// 	//ft_printf("%.*Cfailcheck3 %s i %i j %i k %i%C\n", 0xFF00FF, str, i, j, k);
// 	return (0);
// }

// int	ok_checknum2a(int numbers[100], int check[100], char *str, int i, int *j, int *k)
// {
// 	ok_tests2b(str, check);
// 	//ft_printf("%.*CAChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, *j, *k);
// 	//ft_printf("%.*CAC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
// 	i = 0;
// 	while (str[i] && str[i] != '?')
// 	{
// 		if (str[i] == '#')
// 		{
// 			if (numbers[*j] > check[*k])
// 		s2[i] = 0;	{
// 				//ft_printf("%.*CAfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
// 				return (0);
// 			}
// 			while (str[i] == '#')
// 				++i;
// 			if (str[i] != '?')
// 			{
// 				if (numbers[*j] != check[*k])
// 				{
// 					//ft_printf("%.*CAfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
// 					return (0);
// 				}
// 				++*k;
// 				++*j;
// 			}
// 		}
// 		else
// 			++i;
// 	}
// 	//ft_printf("Apassed check 1 %s i %i j %i k %i\n", str, i, *j, *k);
// 	return (1);
// }

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
	s[i] = 0;
	s[i + 1] = 0;
	s[i + 2] = 0;
	//return (s);
}

int	ok_checknumbers2(char *str, int numbers[100], int s, int num, long long array[100][500])
{
	int		i;
	int		ii;
	int		j;
	int		k;
	int		x;
	char	s1[500];

	i = s;
	j = num;
	k = 0;
	// if (array[num][s] < 0)
		// array[num][s] = 0;
	ft_printf("solving1 %s, j %i, i %i\n", str, j, i);
	if (!ft_strchr(str, '?') && numbers[num])
	{
		array[num][s] = 0;
		ft_printf("no ?      %s, j %i, i %i\n", str, j, i);
		return (0);
	}
	if (ft_strchr(str, '?') && !numbers[num])
	{
		array[num][s] = 0;
		ft_printf("no num    %s, j %i, i %i\n", str, j, i);
		return (0);
	}
	if (!ft_strchr(str, '?') && !numbers[num])
	{
		array[num][s] = 1;
		ft_printf("solution  %s, j %i, i %i\n", str, j, i);
		return (1);
	}
	ft_printf("solving2 %s, j %i, i %i\n", str, j, i);
	// if (!ok_checknum2(numbers, check, str, i, j, k))
	// {
	// 	//ft_printf("%.*C%s ko%C\n", 0xFF0000, str);
	// 	return (0);
	// }
	//ft_printf("%s ok\n", str);
	ok_strcpyspace2(str, s1);
	x = 1;
	i = 0;
	j = 0;
	ft_printf("Sarray[%i][%i] = %i\n", num, s, array[num][s]);
	while (s1[i] && x)
	{
		k = 0;
		while (s1[i] == '#')
		{
			++i;
			++k;
		}
		if (k == numbers[j])
			++j;		
		if (s1[i] == '?')
		{
			ft_printf("solving3 %s, j %i, i %i array %3i\n", str, j, i, array[1][4]);
			s1[i] = '.';
			//ft_printf("XXXi %i j %i num[j] %i %s\n", i, j, numbers[j], s1);
			if (array[j][i] < 0)
			{
				ft_printf("dot added1_%s, j %i, i %i array %3i\n", s1, j, i, array[j][i]);
				x = ok_checknumbers2(s1, numbers, i, j, array);
				ft_printf("dot added2_%s, j %i, i %i array %3i\n", s1, j, i, array[j][i]);
				if (array[num][s] < 0)
					array[num][s] = array[j][i];
				else
					array[num][s] += array[j][i];
				ft_printf("array[%i][%i] = %i\n", j, i, array[j][i]);
				ft_printf("F1array[%i][%i] = %i\n", num, s, array[num][s]);
			}
			else
				array[num][s] += array[j][i];
			ii = i - 1;
			while (ii >= 0 && str[ii] == '#')
			{
				--ii;
				++k;
			}
			s1[i] = '#';
			//ft_printf("YYYi %i j %i num[j] %i %s\n", i, j, numbers[j], s1);
			while ((s1[i] == '#' || s1[i] == '?') && k < numbers[j])
			{
				s1[i] = '#';
				++i;
				++k;
			}
			if (s1[i] && s1[i] != '#')
				s1[i] = '.';
			else if (s1[i])
			{
				ft_printf("array[%i][%i] = %i\n", num, s, array[num][s]);
				return (0);
			}
			//ft_printf("aaa %s\n", s1);
			if (k == numbers[j])
			{
				//ft_printf("aba %s\n", s1);
				++j;
				if (array[j][i] < 0)
				{
					ft_printf("hash added1_%s, j %i, i %i array %3i\n", s1, j, i, array[j][i]);
					x += 2 * ok_checknumbers2(s1, numbers, i, j, array);
					ft_printf("hash added2_%s, j %i, i %i array %3i\n", s1, j, i, array[j][i]);
					if (array[num][s] < 0)
						array[num][s] = array[j][i];
					else
						array[num][s] += array[j][i];
					ft_printf("array[%i][%i] = %i\n", j, i, array[j][i]);
					ft_printf("F2array[%i][%i] = %i\n", num, s, array[num][s]);
				}
				else
					array[num][s] += array[j][i];
			}
			else
			{
				return (0);
			}
			if (s1[i])
				s1[i] = '?';
			break ;
		}
		++i;
	}
	ft_printf ("%.*C2r %s %i %i%C\n",0xFFFF00, s1, j, i);
	ft_printf("array[%i][%i] = %i\n", num, s, array[num][s]);
	//free(s1);
	//array[num][s] = 1;
	if (x)
		return (1);
	return (0);
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
		ft_printf("t = %lli\n", t);
		//free(s);
		//ft_printf("t[2] = %lli\n", t[2]);
		y = 0;
		while (y < 100)
		{
			x = 0;
			while (x < 500)
			{
				if (array[y][x] > 0)
					t += array[y][x];
				++x;
			}
			++ y;
		}
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
	line = ft_readfile("test2", 65536);
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
