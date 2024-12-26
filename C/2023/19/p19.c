/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p19.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/19 10:27:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

typedef struct s_instr
{
	char	name[10];
	char	**rules;
}	t_ins;

typedef struct s_part
{
	int		x;
	int		m;
	int		a;
	int		s;
	char	res;
}	t_part;

typedef struct s_part2
{
	int		xmax;
	int		mmax;
	int		amax;
	int		smax;
	int		xmin;
	int		mmin;
	int		amin;
	int		smin;
	char	res;
	char	**rules;
	int		r;
}	t_part2;

void	ok_createins(char *str, t_ins *ins)
{
	int		i;
	int		j;
	char	s[100];

	i = 0;
	while (str[i] != '{')
	{
		ins->name[i] = str[i];
		++i;
	}
	ins->name[i] = 0;
	++i;
	j = 0;
	while  (str[i] != '}')
	{
		s[j] = str[i];
		++j;
		++i;
	}
	s[j] = 0;
	ins->rules = ft_split(s, ',');
}

void	ok_createpart(char *str, t_part *part)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		++i;
	++i;
	part->x = ft_atoi(&str[i]);
	while (str[i] != '=')
		++i;
	++i;
	part->m = ft_atoi(&str[i]);
	while (str[i] != '=')
		++i;
	++i;
	part->a = ft_atoi(&str[i]);
	while (str[i] != '=')
		++i;
	++i;
	part->s = ft_atoi(&str[i]);
	part->res = 0;
}

int	ok_findins(t_ins ins[1000], char *n)
{
	int	j;

	j = 0;
	ft_printf("ins %s\n", n);
	while(ft_strncmp(ins[j].name, n, 8))
	{
		++j;
	}
	return (j);
}

void	ok_processrule(int r, int j, t_part *part, t_ins ins[1000])
{
	int	v;
	int	b;
	int	i;

	b = 0;
	v = 0;
	ft_printf("part x %i, m %i, a %i, s %i, res %i\n", part->x, part->m, part->a, part->s, part->res);
	ft_printf("%s:%s\n", ins[j].rules[r],ins[j].rules[r + 1]);
	if (ins[j].rules[r][0] == 'A')
		part->res = 'A';
	else if (ins[j].rules[r][0] == 'R')
		part->res = 'R';
	else if (ins[j].rules[r][1] != '>' && ins[j].rules[r][1] != '<')
		ok_processrule(0, ok_findins(ins, ins[j].rules[r]), part, ins);
	else
	{
		ft_printf("b\n");
		if (ins[j].rules[r][0] == 'x')
			v = part->x;
		else if (ins[j].rules[r][0] == 'm')
			v = part->m;
		else if (ins[j].rules[r][0] == 'a')
			v = part->a;
		else if (ins[j].rules[r][0] == 's')
			v = part->s;
		ft_printf("v %i b %i\n", v, b);
		if (ins[j].rules[r][1] == '>')
		{
			if (v > ft_atoi(&ins[j].rules[r][2]))
				b = 1;
		}
		else if (ins[j].rules[r][1] == '<')
		{
			if (v < ft_atoi(&ins[j].rules[r][2]))
				b = 1;
		}
		ft_printf("v %i b %i\n", v, b);
		if (!b)
			ok_processrule(r + 1, j, part, ins);
		else
		{
			i = 0;
			while (ins[j].rules[r][i] != ':')
				++i;
			++i;
			if (ins[j].rules[r][i] == 'A')
				part->res = 'A';
			else if (ins[j].rules[r][i] == 'R')
				part->res = 'R';
			else if (ins[j].rules[r][i + 1] != '>' && ins[j].rules[r][i + 1] != '<')
				ok_processrule(0, ok_findins(ins, &ins[j].rules[r][i]), part, ins);
		}
	}
	
}

void	ok_processpart(t_part *part, t_ins ins[1000], int max)
{
	int	j;
	int	r;

	j = ok_findins(ins, "in");
	r = 0;
	while (!part->res)
	{
		ok_processrule(r, j, part, ins);
	}
	(void)max;
}

void	ok_update(char **line, long long *ptot, int i, int j)
{
	t_ins		ins[1000];
	t_part		part[1000];
	long long	r;
	int			mins;
	int			mpart;

	j = 0;
	r = 0;
	while (line[j] && line[j][0] != '{')
	{
		ok_createins(line[j], &ins[j]);
		++j;
	}
	mins = j;
	i = 0;
	while (line[j])
	{
		ok_createpart(line[j], &part[i]);
		++j;
		++i;
	}
	mpart = i;
	i = 0;
	ft_printf("aaa\n");
	while (i < mpart)
	{
		ok_processpart(&part[i], ins, mins);
		if (part[i].res == 'A')
		{
			r += part[i].x + part[i].m + part[i].a + part[i].s;
		}
		++i;
	}
	*ptot = r;
}

void	ok_copypart(t_part2 part[5000], int i, int *max)
{
	part[*max].xmin = part[i].xmin;
	part[*max].xmax = part[i].xmax;
	part[*max].mmin = part[i].mmin;
	part[*max].mmax = part[i].mmax;
	part[*max].amin = part[i].amin;
	part[*max].amax = part[i].amax;
	part[*max].smin = part[i].smin;
	part[*max].smax = part[i].smax;
	part[*max].r = part[i].r;
	part[*max].res = part[i].res;
	part[*max].rules = part[i].rules;
}
void	ok_processrule2(t_ins ins[1000], t_part2 part[5000], int i, int *max)
{
	char	**rules;
	int		r;
	int		j;

	r = part[i].r;
	rules = part[i].rules;
	r = part[i].r;
	ft_printf("ZZZi %i, max %i rule %s:%s", i, r, rules[r], rules[r + 1]);
	ft_printf("part x: %4i-%4i, m: %4i-%4i, a: %4i-%4i, s: %4i-%4i\n", part[i].xmin, part[i].xmax, part[i].mmin, part[i].mmax, part[i].amin, part[i].amax, part[i].smin, part[i].smax);
	if (rules[r][0] == 'A')
		part[i].res = 'A';
	else if (rules[r][0] == 'R')
		part[i].res = 'R';
	else if (rules[r][1] != '>' && rules[r][1] != '<')
	{
		part[i].r = 0;
		part[i].rules = ins[ok_findins(ins, rules[r])].rules;
		ok_processrule2(ins, part, i, max);
	}
	else
	{
		ok_copypart(part, i, max);
		if (rules[r][0] == 'x')
		{
			if (rules[r][1] == '<')
			{
				part[i].xmax = ft_atoi(&rules[r][2]) - 1;
				part[*max].xmin = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
			else
			{
				part[i].xmin = ft_atoi(&rules[r][2]) + 1;
				part[*max].xmax = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
		}
		else if (rules[r][0] == 'm')
		{
			if (rules[r][1] == '<')
			{
				part[i].mmax = ft_atoi(&rules[r][2]) - 1;
				part[*max].mmin = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
			else
			{
				part[i].mmin = ft_atoi(&rules[r][2]) + 1;
				part[*max].mmax = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
		}
		else if (rules[r][0] == 'a')
		{
			if (rules[r][1] == '<')
			{
				part[i].amax = ft_atoi(&rules[r][2]) - 1;
				part[*max].amin = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
			else
			{
				part[i].amin = ft_atoi(&rules[r][2]) + 1;
				part[*max].amax = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
		}
		else if (rules[r][0] == 's')
		{
			if (rules[r][1] == '<')
			{
				part[i].smax = ft_atoi(&rules[r][2]) - 1;
				part[*max].smin = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
			else
			{
				part[i].smin = ft_atoi(&rules[r][2]) + 1;
				part[*max].smax = ft_atoi(&rules[r][2]);
				part[*max].r += 1;
				++(*max);
				j = 0;
				while (rules[r][j] != ':')
					++j;
				++j;
				if (rules[r][j] == 'A')
					part[i].res = 'A';
				else if (rules[r][j] == 'R')
					part[i].res = 'R';
				else
				{
					part[i].r = 0;
					part[i].rules = ins[ok_findins(ins, &rules[r][j])].rules;
					ok_processrule2(ins, part, i, max);
				}
			}
		}
	}
	
}

void	ok_processpart2(t_part2 part[5000], int i, t_ins ins[1000], int *max)
{
	ft_printf("yyy\n");
	ok_processrule2(ins, part, i, max);
}

void	ok_update2(char **line, long long *ptot, int i, int j)
{
	t_ins		ins[1000];
	t_part2		part[5000];
	long long	r;
	int			mins;
	int			mpart;

	j = 0;
	r = 0;
	while (line[j] && line[j][0] != '{')
	{
		ok_createins(line[j], &ins[j]);
		++j;
	}
	mins = j;
	(void)mins;
	i = 0;
	part[0].xmin = 1;
	part[0].xmax = 4000;
	part[0].mmin = 1;
	part[0].mmax = 4000;
	part[0].amin = 1;
	part[0].amax = 4000;
	part[0].smin = 1;
	part[0].smax = 4000;
	part[0].r = 0;
	part[0].res = 0;
	part[0].rules = ins[ok_findins(ins, "in")].rules;
	mpart = 1;
	i = 0;
	ft_printf("xxx\n");
	while (i < mpart)
	{
		ok_processpart2(part, i, ins, &mpart);
		++i;
	}
	i = 0;
	while (i < mpart)
	{
		if (part[i].res == 'A')
			r += (long long)(part[i].xmax - part[i].xmin + 1)
				* (long long)(part[i].mmax - part[i].mmin + 1)
				* (long long)(part[i].amax - part[i].amin + 1)
				* (long long)(part[i].smax - part[i].smin + 1);
		++i;
	}
	*ptot = r;
}

int	main(void)
{
	char		**line;
	//char		**lines;
	int			i;
	int			j;
	long long	total[2];

	total[0] = 0;
	total[1] = 0;
	line = NULL;
	i = 1;
	line = ft_readfile("input", 65536);
	//lines = ft_split(line[0], '');
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
