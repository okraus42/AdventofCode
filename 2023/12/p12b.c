/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p12b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/19 12:19:39 by okraus           ###   ########.fr       */
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
// 	ok_tests2b(str, check);
// 	ft_printf("%.*CChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, j, k);
// 	ft_printf("%.*CC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
// 	while (str[i] && str[i] != '?')
// 	{
// 		if (str[i] == '#')
// 		{
// 			if (numbers[j] > check[k])
// 			{
// 				ft_printf("%.*Cfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 				return (0);
// 			}
// 			while (str[i] == '#')
// 				++i;
// 			if (str[i] != '?')
// 			{
// 				if (numbers[j] != check[k])
// 				{
// 					ft_printf("%.*Cfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
// 					return (0);
// 				}
// 				++k;
// 				++j;
// 			}
// 		}
// 		else
// 			++i;
// 	}
// 	ft_printf("passed check 1 %s i %i j %i k %i\n", str, i, j, k);
// 	while (numbers[j])
// 	{
// 		if (!check[k] && !check[k + 1])
// 		{
// 			ft_printf("%.*Ccheck[%i] %i%C\n", 0xFF0000, k, check[k]);
// 			ft_printf("%.*Cfailcheck2 %s i %i j %i k %i%C\n", 0xFF0000, str, i, j, k);
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
// 	ft_printf("passed check 2 %s i %i j %i k %i\n", str, i, j, k);
// 	if (str[i])
// 	{
// 		ft_printf("%.*Cpassed check 3a %s i %i j %i k %i\n", 0xFFFF00, str, i, j, k);
// 		return (1);
// 	}
// 	if ((!check[k] && !check[k + 1]))
// 	{
// 		ft_printf("%.*Cpassed check 3b %s i %i j %i k %i\n", 0x00FFFF, str, i, j, k);
// 		return (1);
// 	}
// 	ft_printf("%.*Cfailcheck3 %s i %i j %i k %i%C\n", 0xFF00FF, str, i, j, k);
// 	return (0);
// }

// int	ok_checknum2a(int numbers[100], int check[100], char *str, int i, int *j, int *k)
// {
// 	ok_tests2b(str, check);
// 	ft_printf("%.*CAChecking %s i %i j %i k %i%C\n", 0xFFFFFF, str, i, *j, *k);
// 	ft_printf("%.*CAC[0] %i, C[1] %i, C[2] %i, C[3] %i, C[4] %i, C[5] %i%C\n", 0xFFFFFF, check[0], check[1], check[2], check[3], check[4], check[5]);
// 	i = 0;
// 	while (str[i] && str[i] != '?')
// 	{
// 		if (str[i] == '#')
// 		{
// 			if (numbers[*j] > check[*k])
// 			{
// 				ft_printf("%.*CAfailcheck1a %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
// 				return (0);
// 			}
// 			while (str[i] == '#')
// 				++i;
// 			if (str[i] != '?')
// 			{
// 				if (numbers[*j] != check[*k])
// 				{
// 					ft_printf("%.*CAfailcheck1b %s i %i j %i k %i%C\n", 0xFF0000, str, i, *j, *k);
// 					return (0);
// 				}
// 				++*k;
// 				++*j;
// 			}
// 		}
// 		else
// 			++i;
// 	}
// 	ft_printf("Apassed check 1 %s i %i j %i k %i\n", str, i, *j, *k);
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
	//return (s);
}

// int	ok_check2(char *str, int numbers[100], int j)
// {
// 	char	*tmp;
// 	int		i;
// 	int		h;
// 	int		check[100];

// 	i = 0;
// 	(void)h;
// 	while (i <= j)
// 	{
// 		check[i] = numbers[i];
// 		++i;
// 	}
// 	while (i < 100)
// 	{
// 		check[i] = 0;
// 		++i;
// 	}
// 	tmp = ft_strdup(str);
// 	ft_printf("c2 %s %i\n", tmp, j);
// 	i = ft_strlen(tmp) - 1;
// 	while (i >= 0)
// 	{
// 		if (str[i] == '#' && j >= 0 && check[j])
// 			--check[j];
// 		else if (str[i] == '#')
// 			--j;
// 		--i;
// 	}
// 	free(tmp);
// 	if (j < 0)
// 		return (0);
// 	else
// 	{
// 		ft_printf("ok\n");
// 		return (1);
// 	}
// }

// int	ok_check3b(char *str, int *i, int check)
// {
// 	int	tmp;
// 	int	j;

// 	j = *i;
// 	tmp = check;
// 	while (j >= 0 && tmp > 0)
// 	{
// 		if (str[j] == '.')
// 			return (0);
// 		--j;
// 		--tmp;
// 	}
// 	if (str[j] == '#')
// 		return (0);
// 	if (tmp)
// 		return (0);
// 	if (j)
// 		*i = j - 1;
// 	else
// 		*i = 0;
// 	return (1);
// }

// int	ok_check3c(char *str, int i, int check)
// {

// 	while (i >= 0 && check >= 0)
// 	{
// 		if (str[i] == '.')
// 			return (0);
// 		--i;
// 		--check;
// 	}
// 	if (check)
// 		return (0);
// 	if (i >= 0 && str[i] == '#')
// 		return (0);
// 	return (1);
// }

// int	ok_check3(char *str, int numbers[100], int j)
// {
// 	char	*tmp;
// 	int		i;
// 	int		check[100];

// 	i = 0;
// 	while (i <= j)
// 	{
// 		check[i] = numbers[i];
// 		++i;
// 	}
// 	while (i < 100)
// 	{
// 		check[i] = 0;
// 		++i;
// 	}
// 	tmp = ft_strdup(str);
// 	ft_printf("c3 %s %i\n", tmp, j);
// 	i = ft_strlen(tmp) - 1;
// 	while (i >= 0)
// 	{
// 		if (tmp[i] == '#' && ok_check3c(tmp, i, check[j]))
// 		{
// 			free(tmp);
// 			return (0);
// 		}
// 		if (j >= 0 && ok_check3b(tmp, &i, check[j]))
// 		{
// 			--j;
// 		}
// 		else
// 			--i;
// 	}
// 	free(tmp);
// 	if (j >= 0)
// 		return (0);
// 	else
// 	{
// 		ft_printf("ok\n");
// 		return (1);
// 	}
// }

int	ok_check(char *str, int i, int numbers[100], int j)
{
	int	h;

	if (!str[i])
		return (0);
	if (str[i] == '.')
		return (0);
	h = numbers[j];
	while (h && str[i] && str[i] != '.')
	{
		--h;
		++i;
	}
	if (!h && str[i] != '#')
	{
		//ft_printf("pass\n");
		return (1);
	}
	//ft_printf("fail\n");
	return (0);
	// num = numbers[j];
	// if (str[i] == '.' || str[i + 1] == '#')
	// 	return (0);
	// tmp = ft_string_copy_n(str, i + 1);
	// tmp[i + 1] = 0;
	// while (i >= 0 && num)
	// {
	// 	if (tmp[i] != '.')
	// 		tmp[i] = '#';
	// 	else
	// 	{
	// 		free(tmp);
	// 		return(0);
	// 	}
	// 	--i;
	// 	--num;
	// }
	// //ft_printf("test\n");
	// if (num || (i >= 0 && str[i] == '#'))
	// {
	// 	free(tmp);
	// 	return (0);
	// }
	// if (!ok_check2(tmp, numbers, j) || !ok_check3(tmp, numbers, j))
	// {
	// 	free(tmp);
	// 	return (0);
	// }
	// //ft_printf("pass i %i \n", i);
	// if (i < 0)
	// 	*k = i + 1;
	// else
	// 	*k = i;
	// ft_printf("%s\n", tmp);
	// free (tmp);
	// // while (i >= 0)
	// // {
	// // 	if (str[i] == '#')
	// // 		return (0);
	// // 	--i;
	// // }
	// return (1);
}

int	ok_checkmin(char *str, int j, int i, int numbers[100])
{
	int	ii;
	int	jj;
	int	h;

	ii = i;
	jj = j + 1;
	h = 0;
	ft_printf("CMIN %i %i\n", j, i);
	while (str[ii])
	{
		if (str[ii] == '#')
			++h;
		if (numbers[jj] && numbers[jj] == h)
		{
			h = 0;
			++jj;
		}
		++ii;
	}
	if (h)
		return (1);
	return (1);
}

void	ok_setminmax(int minmax[100][2], int j, char *str, int numbers[100])
{
	int	i;
	int	ii;
	int	hash;

	i = 0;
	minmax[j][0] = ft_strlen(str);
	if (!j)
	{
		while (str[i])
		{
			ii = i;
			hash = numbers[j];
			while (hash && str[ii] && str[ii] != '.')
			{
				++ii;
				--hash;
			}
			if (!hash && str[ii] != '#' && ok_checkmin(str, j, i, numbers))
			{
				minmax[j][0] = ii - numbers[j];
				ft_printf("min %i = %i\n", j, ii - numbers[j]);
				break;
			}
			++i;
		}
		while (str[i] && str[i] != '#')
		{
			++i;
		}
		hash = numbers[j];
		ii = i;
		while (hash && str[ii] && str[ii] != '.')
		{
			++ii;
			--hash;
		}
		if (!hash && str[ii] != '#')
		{
			minmax[j][1] = ii - numbers[j];
			ft_printf("max %i = %i\n", j, ii);
			return ;
		}
		else if (hash)
		{
			while (str[i] == '#' || str[i] == '?')
				++i;
			//ft_printf("hash 00 %i\n", i);
			while (i >= 0)
			{
				ii = i;
				hash = numbers[j];
				while (ii >= 0 && str[ii] != '.')
				{
					--hash;
					if ((!hash && !ii) || (!hash && str[ii] != '#'))
					{
						minmax[j][1] = ii;
						ft_printf("max %i = %i\n", j, ii);
						return ;
					}
					--ii;
				}
				--i;
			}
		}
		else //!hash
		{
			while (str[i] == '#')
				++i;
			//ft_printf("no hash 0\n");
			while (i >= 0)
			{
				ii = i;
				hash = numbers[j];
				while (ii >= 0 && str[ii] != '.' && str[i + 1] != '#')
				{
					--hash;
					if ((!hash && !ii) || (!hash && str[ii] != '#'))
					{
						minmax[j][1] = ii;
						ft_printf("max %i = %i\n", j, ii);
						return ;
					}
					--ii;
				}
				--i;
			}
		}
	}
	else		//BETTER START CHECKING for remaining numbers
	{
		i = minmax[j - 1][0] + 1 + numbers[j - 1];
		while (str[i - 2] && str[i - 1] && str[i])
		{
			ii = i;
			hash = numbers[j];
			while (hash && str[ii] && str[ii] != '.')
			{
				++ii;
				--hash;
			}
			if (!hash && str[ii] != '#' && ok_checkmin(str, j, i, numbers))
			{
				ft_printf("START %s | %s | %i\n", &str[ii], &str[ii - numbers[j]], numbers[j]);
				minmax[j][0] = ii - numbers[j];
				break;
			}
			++i;
		}
		while (str[i] && str[i] != '#')
		{
			++i;
		}
		hash = numbers[j];
		ii = i;
		while (hash && str[ii] && str[ii] != '.')
		{
			++ii;
			--hash;
		}
		if (!hash && str[ii] != '#')
		{
			ft_printf("first return %i\n", i);
			minmax[j][1] = ii - numbers[j];
			return ;
		}
		else if (hash)
		{
			while (str[i] == '#' || str[i] == '?')
				++i;
			ft_printf("hash %i\n", i);
			while (i >= 0)
			{
				ii = i;
				hash = numbers[j];
				while (ii >= 0 && str[ii] != '.')
				{
					--hash;
					if ((!hash && !ii) || (!hash && str[ii] != '#'))
					{
						minmax[j][1] = ii;
						return ;
					}
					--ii;
				}
				--i;
			}
		}
		else //!hash
		{
			while (str[i] == '#')
				++i;
			while (i >= 0)
			{
				ii = i;
				ft_printf("BW | %s %i\n", &str[ii], ii);
				hash = numbers[j];
				while (ii >= 0 && str[ii] != '.' && str[i + 1] != '#')
				{
					ft_printf("%s %i\n", &str[ii], ii);
					--hash;
					if ((!hash && !ii) || (!hash && str[ii] != '#'))
					{
						ft_printf("no hash %i\n", ii);
						minmax[j][1] = ii;
						return ;
					}
					--ii;
				}
				--i;
			}
		}
		//ft_printf("no return\n");
	}
}

void	ok_findk(int i, int j, int *k, int numbers[100])
{
	if (!j)
		*k = 1;
	else
		*k = i - numbers[j - 1];
}

long long	ok_checknumbers2(char *str, int numbers[100], long long	array[100][500])
{
	int			i;
	int			j;
	int			k;
	long long	r;
	int			nmax;
	int			smax;
	int			minmax[100][2];

	nmax = 0;
	smax = 0;
	i = 0;
	while (i < 100)
	{
		minmax[i][0] = 0;
		minmax[i][1] = 0;
		++i;
	}
	while (str[smax])
		++smax;
	while (numbers[nmax])
		++nmax;
	i = 0;
	j = 0;
	r = 0;
	while (j < nmax)
	{
		i = 0;
		ok_setminmax(minmax, j, str, numbers);
		i = minmax[j][0];
		ft_printf("iii %i %i %i\n", i, minmax[j][0], minmax[j][1]);
		while (i < smax)
		{
			if (ok_check(str, i, numbers, j) && i <= minmax[j][1])
			{
				ok_findk(i, j, &k, numbers);
				ft_printf("k %i arr[%i] %i n %i\n", k, array[j][k], j, numbers[j]);
				array[j + 1][i + 1] = array[j][k] + array[j + 1][i];
				r = array[j + 1][i + 1];
			}
			else
			{
				array[j + 1][i + 1] = array[j + 1][i];
				r = array[j + 1][i + 1];
			}
			ft_printf("i %i j %i r %i\n", i, j, r);
			++i;
		}
		++j;
	}
	ft_printf("r2 %i\n", r);
	return (r);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	int			numbers[100];
	//int			check[100];
	char		newline[500];
	long long	array[100][500];
	char		s[500];
	int			qm;
	int		c;

	j = 0;
	//c = 0;
	while (line[j])
	{
		qm = 0;
		i = 0;
		
		ok_getnewline(newline, line[j]);
		ok_getnumbers(newline, numbers, i, &qm);
		ok_strcpyspace2(newline, s);
		ft_memset(array, 0, sizeof(array));
		while (i < 500)
		{
			array[0][i] = 1;
			++i;
		}
		ft_printf("newline: %s\n", newline);
		//ft_printf("s %s\n", s);
		i = 0;
		while (numbers[i])
		{
			//ft_printf("%i ", numbers[i]);
			++i;
		}
		//ft_printf("\n");
		*ptot += ok_checknumbers2(s, numbers, array);
		c = 0;
		while (c < 10)
		{
			i = 0;
			while (i < 20)
			{
				ft_printf("%5i |", array[c][i]);
				++i;
			}
			ft_printf("\n");
			++c;
		}
		//free(s);
		//t[2] = t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0] * t[1] / t[0];
		// if (t[1] % t[0])
		// 	ft_printf("CC = %2i\n", ++c);
		//ft_printf("t[2] = %lli\n", t[2]);
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
