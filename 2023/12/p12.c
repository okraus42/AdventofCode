/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p12.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/12 19:47:10 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

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
	iters = 5;
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

void	ok_tests2b(char *str, int check[100])
{
	int	i;
	int	t;
	int	b;

	i = 0;
	t = 0;
	b = 0;
	while (str[i])
	{
		//ft_printf("char %i = %c\n", i, str[i]);
		if (str[i] == '#' || str[i] == '?')
		{
			//ft_printf("++t\n");
			++t;
		}
		else if (i > 0 && (str[i - 1] == '#' || str[i - 1] == '?'))
		{
			//ft_printf("reset\n");
			check[b] = t;
			t = 0;
			++b;
		}
		//ft_printf("%i %i %i\n", i > 0, str[i - 1] == '#', i > 0 && str[i - 1] == '#');
		//ft_printf("%i %i %i\n", i, t, b);
		++i;
	}
	if (t)
	{
		check[b] = t;
		check[b + 1] = 0;
		check[b + 2] = 0;
	}
	else
	{
		check[b] = 0;
		check[b + 1] = 0;
	}
}

int	ok_checknum2(int numbers[100], int check[100], char *str, int i, int j, int k)
{
	int	hash;


	ok_tests2b(str, check);
	//ft_printf("%.*CChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, j, k);
	//ft_printf("%.*CC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
	while (str[i] && str[i] != '?')
	{
		if (str[i] == '#')
		{
			hash = 0;
			if (numbers[j] > check[k])
			{
				//ft_printf("%.*Cfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
				return (0);
			}
			while (str[i] == '#')
			{
				++i;
				++hash;
			}
			if (numbers[j] < hash)
			{
				//ft_printf("%.*Cfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
				return (0);
			}
			if (str[i] != '?')
			{
				if (numbers[j] != check[k])
				{
					//ft_printf("%.*Cfailcheck1c %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
					return (0);
				}
				++k;
				++j;
			}
		}
		else
			++i;
	}
	//ft_printf("passed check 1 %s i %i j %i k %i\n", str, i, j, k);
	while (numbers[j])
	{
		if (!check[k] && !check[k + 1])
		{
			//ft_printf("%.*Ccheck[%i] %i%C\n", 0xFF0000, k, check[k]);
			//ft_printf("%.*Cfailcheck2 %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
			return (0);
		}
		if (check[k] > numbers[j])
		{
			check[k] -= (numbers[j] + 1);
			++j;
		}
		else if (check[k] == numbers[j])
		{
			++j;
			++k;
		}
		else
			++k;
	}
	//ft_printf("passed check 2 %s i %i j %i k %i\n", str, i, j, k);
	if (str[i])
	{
		//ft_printf("%.*Cpassed check 3a %s i %i j %i k %i%C\n", 0xFFFF00, str, i, j, k);
		return (1);
	}
	if ((!check[k] && !check[k + 1]))
	{
		//ft_printf("%.*Cpassed check 3b %s i %i j %i k %i%C\n", 0x00FFFF, str, i, j, k);
		return (1);
	}
	//ft_printf("%.*Cfailcheck3 %s i %i j %i k %i%C\n", 0xFF00FF, str, i, j, k);
	return (0);
}

int	ok_checknum2a(int numbers[100], int check[100], char *str, int i, int *j, int *k)
{
	ok_tests2b(str, check);
	//ft_printf("%.*CAChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, *j, *k);
	//ft_printf("%.*CAC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
	i = 0;
	while (str[i] && str[i] != '?')
	{
		if (str[i] == '#')
		{
			if (numbers[*j] > check[*k])
			{
				//ft_printf("%.*CAfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
				return (0);
			}
			while (str[i] == '#')
				++i;
			if (str[i] != '?')
			{
				if (numbers[*j] != check[*k])
				{
					//ft_printf("%.*CAfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
					return (0);
				}
				++*k;
				++*j;
			}
		}
		else
			++i;
	}
	//ft_printf("Apassed check 1 %s i %i j %i k %i\n", str, i, *j, *k);
	return (1);
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
	s[i] = 0;
	//return (s);
}

int	ok_checknumbers2(char *str, int numbers[100], int check[100], int qm, long long *r, long long *q)
{
	int		i;
	int		ii;
	int		j;
	int		k;
	int		x;
	char	s1[256];

	++(*q); 
	i = 0;
	j = 0;
	k = 0;
	if (!ok_checknum2(numbers, check, str, i, j, k))
	{
		//ft_printf("%.*C%s ko%C\n", 0xFF0000, str);
		return (0);
	}
	//ft_printf("%s ok\n", str);
	ok_strcpyspace2(str, s1);
	i = 0;
	x = 1;
	while (s1[i] && x)
	{
		if (s1[i] == '?')
		{
			j = 0;
			k = 0;
			s1[i] = '.';
			//ft_printf("XXXi %i j %i num[j] %i %s\n", i, j, numbers[j], s1);
			x = ok_checknumbers2(s1, numbers, check, qm, r, q);
			if (ok_checknum2a(numbers, check, str, i, &j, &k))
			{
				k = 0;
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
					return (0);
				//ft_printf("aaa %s\n", s1);
				if (k == numbers[j])
				{
					//ft_printf("aba %s\n", s1);
					x += 2 * ok_checknumbers2(s1, numbers, check, qm, r, q);
				}
				else
					return (0);
			}
			s1[i] = '?';
			break ;
		}
		++i;
	}
	if (!x)
	{
		//ft_printf ("%.*C2r %s %i%C\n",0xFF00FF, s1, *r);
		//free(s1);
		return (0);
	}
	//ft_printf ("%.*C2r %s %i%C\n",0xFFFF77, s1, *r);
	if (!ft_strchr(s1, '?'))
		++(*r); 
	//ft_printf ("%.*C2r %s %i%C\n",0xFFFF00, s1, *r);
	//free(s1);
	return (1);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int		numbers[100];
	int		check[100];
	char	newline[500];
	char	s[500];
	int		qm;
	long long	t[3];
	//int		c;

	j = 0;
	//c = 0;
	while (line[j])
	{
		qm = 0;
		ok_getnumbers(line[j], numbers, i, &qm);
		t[0] = ok_checknumbers(line[j], numbers, check, qm);
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
		t[1] = 0;
		t[2] = 0;
		ok_checknumbers2(s, numbers, check, qm, &t[1], &t[2]);
		ft_printf("t[0] = %lli\n", t[0]);
		ft_printf("t[1] = %lli t[2] = %lli\n", t[1], t[2]);
		//free(s);
		//t[2] = t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0];
		// if (t[1] % t[0])
		// 	ft_printf("CC = %2i\n", ++c);
		//ft_printf("t[2] = %lli\n", t[2]);
		*ptot += t[1];
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
	ft_printf("t1=%5lld\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	return (0);
}
