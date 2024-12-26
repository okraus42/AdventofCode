/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:57:35 by okraus            #+#    #+#             */
/*   Updated: 2023/12/03 07:22:17 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

// typedef struct s_cubes
// {
// 	int	red;
// 	int	green;
// 	int	blue;
// 	int	mr;
// 	int	mg;
// 	int	mb;
// }	t_cubes;


// void	ok_update(char *str, int *ptot, int i, int j)
// {
// 	t_cubes	cubes;
// 	char	**split;
// 	int		num;
// 	int		id;

// 	id = 0;
// 	i = 0;
// 	cubes.red = 0;
// 	cubes.blue = 0;
// 	cubes.green = 0;
// 	while(str[i] && str[i] != ':')
// 	{
// 		if (!id && ft_isdigit(str[i]))
// 		{
// 			id = ft_atoi(&str[i]);
// 		}
// 		++i;
// 	}
// 	if (str[i])
// 		++i;
// 	split = ft_split(&str[i], ';');
// 	i = 0;
// 	while (split[i])
// 	{
// 		j = 0;
// 		while (split[i][j])
// 		{
// 			if (!num && ft_isdigit(split[i][j]))
// 			{
// 				num = ft_atoi(&split[i][j]);
// 			}
// 			else if (num && !ft_isdigit(split[i][j]))
// 			{
// 				if (!ft_strncmp(&split[i][j], "blue", 4))
// 				{
// 					cubes.blue = num;
// 					num = 0;
// 				}
// 				else if (!ft_strncmp(&split[i][j], "red", 3))
// 				{
// 					cubes.red = num;
// 					num = 0;
// 				}
// 				else if (!ft_strncmp(&split[i][j], "green", 5))
// 				{
// 					cubes.green = num;
// 					num = 0;
// 				}
// 			}
// 			++j;
			
// 		}
// 		ft_printf("r %3i, g %3i, b %3i\n", cubes.red, cubes.green, cubes.blue);
// 		if (cubes.red > 12 || cubes.green > 13 || cubes.blue > 14)
// 		{
// 			ft_free_split(&split);
// 			return ;
// 		}
// 		++i;
// 	}
// 	ft_free_split(&split);
// 	*ptot += id;
// }

// void	ok_update2(char *str, int *ptot, int i, int j)
// {
// 	t_cubes	cubes;
// 	char	**split;
// 	int		num;
// 	int		id;

// 	id = 0;
// 	i = 0;
// 	cubes.red = 0;
// 	cubes.blue = 0;
// 	cubes.green = 0;
// 	cubes.mr = 0;
// 	cubes.mg = 0;
// 	cubes.mb = 0;
// 	while(str[i] && str[i] != ':')
// 	{
// 		if (!id && ft_isdigit(str[i]))
// 		{
// 			id = ft_atoi(&str[i]);
// 		}
// 		++i;
// 	}
// 	if (str[i])
// 		++i;
// 	split = ft_split(&str[i], ';');
// 	i = 0;
// 	while (split[i])
// 	{
// 		j = 0;
// 		while (split[i][j])
// 		{
// 			if (!num && ft_isdigit(split[i][j]))
// 			{
// 				num = ft_atoi(&split[i][j]);
// 			}
// 			else if (num && !ft_isdigit(split[i][j]))
// 			{
// 				if (!ft_strncmp(&split[i][j], "blue", 4))
// 				{
// 					cubes.blue = num;
// 					num = 0;
// 				}
// 				else if (!ft_strncmp(&split[i][j], "red", 3))
// 				{
// 					cubes.red = num;
// 					num = 0;
// 				}
// 				else if (!ft_strncmp(&split[i][j], "green", 5))
// 				{
// 					cubes.green = num;
// 					num = 0;
// 				}
// 			}
// 			++j;
			
// 		}
// 		ft_printf("r %3i, g %3i, b %3i\n", cubes.red, cubes.green, cubes.blue);
// 		if (cubes.red > cubes.mr)
// 			cubes.mr = cubes.red;
// 		if (cubes.blue > cubes.mb)
// 			cubes.mb = cubes.blue;
// 		if (cubes.green > cubes.mg)
// 			cubes.mg = cubes.green;
		
// 		++i;
// 	}
// 	ft_free_split(&split);
// 	ft_printf("mr %3i, mg %3i, mb %3i\n", cubes.mr, cubes.mg, cubes.mb);
// 	*ptot += (cubes.mg * cubes.mr * cubes.mb);
// }

int		ft_issymbol(int c)
{
	if (c > ' ' && c != '.' && !ft_isalnum(c))
		return (1);
	return (0);
}

void	ok_update(char **line, int *ptot, int i, int j)
{
	int	num;
	int skip;

	skip = 0;
	num = 0;
	while (line[j])
	{
		i = 0;
		num = 0;
		skip = 0;
		while (line[j][i])
		{
			if (!num && ft_isdigit(line[j][i]))
			{
				num = ft_atoi(&line[j][i]);
				ft_printf("num = %5d, tot = %7i\n", num, *ptot);
			}
			while (num && ft_isdigit(line[j][i]))
			{
				if (j > 0 && i > 0 && ft_issymbol(line[j - 1][i - 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (i > 0 && ft_issymbol(line[j][i - 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (line[j + 1] && i > 0 && ft_issymbol(line[j + 1][i - 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (j > 0 && ft_issymbol(line[j - 1][i]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (ft_issymbol(line[j][i]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (line[j + 1] && ft_issymbol(line[j + 1][i]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (j > 0 && line[j][i + 1] && ft_issymbol(line[j - 1][i + 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (line[j][i + 1] && ft_issymbol(line[j][i + 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				else if (line[j + 1] && line[j][i + 1] && ft_issymbol(line[j + 1][i + 1]))
				{
					*ptot += num;
					num = 0;
					skip = 1;
				}
				++i;
			}
			if (num)
				num = 0;
			while (skip && ft_isdigit(line[j][i]))
			{
				++i;
			}
			skip = 0;
			++i;
		}
		++j;
	}
}

int	ok_findnum(char **line, int j, int i, int o)
{
	while (i + o > 0 && ft_isdigit(line[j][i + o]))
		--i;
	if (!ft_isdigit(line[j][i + o]))
		++i;
	return(ft_atoi(&line[j][i + o]));
}

void	ok_update2(char **line, int *ptot, int i, int j)
{
	int	num1;
	int	num2;
	int sn;

	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			if (ft_issymbol(line[j][i]) && line[j][i] != '*')
				line[j][i] = '.';
			++i;
		}
		++j;
	}
	j = 0;
	while (line[j])
	{
		i = 0;
		while (line[j][i])
		{
			sn = 0;
			num1 = 0;
			num2 = 0;
			if (line[j][i] == '*')
			{
				if (ft_isdigit(line[j - 1][i - 1]))
					sn++;
				if (ft_isdigit(line[j - 1][i]) && !ft_isdigit(line[j - 1][i - 1]))
					sn++;
				if (ft_isdigit(line[j - 1][i + 1]) && !ft_isdigit(line[j - 1][i]))
					sn++;
				if (ft_isdigit(line[j][i - 1]))
					sn++;
				if (ft_isdigit(line[j][i]) && !ft_isdigit(line[j][i - 1]))
					sn++;
				if (ft_isdigit(line[j][i + 1]) && !ft_isdigit(line[j][i]))
					sn++;
				if (ft_isdigit(line[j + 1][i - 1]))
					sn++;
				if (ft_isdigit(line[j + 1][i]) && !ft_isdigit(line[j + 1][i - 1]))
					sn++;
				if (ft_isdigit(line[j + 1][i + 1]) && !ft_isdigit(line[j + 1][i]))
					sn++;
			}
			if (sn == 2)
			{
				if (ft_isdigit(line[j - 1][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j - 1, i, 0 - 1);
					else
						num2 = ok_findnum(line, j - 1, i, 0 - 1);
				}
				if (ft_isdigit(line[j - 1][i]) && !ft_isdigit(line[j - 1][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j - 1, i, 0);
					else
						num2 = ok_findnum(line, j - 1, i, 0);
				}
				if (ft_isdigit(line[j - 1][i + 1]) && !ft_isdigit(line[j - 1][i]))
				{
					if (!num1)
						num1 = ok_findnum(line, j - 1, i, 0 + 1);
					else
						num2 = ok_findnum(line, j - 1, i, 0 + 1);
				}
				if (ft_isdigit(line[j][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j, i, 0 - 1);
					else
						num2 = ok_findnum(line, j, i, 0 - 1);
				}
				if (ft_isdigit(line[j][i]) && !ft_isdigit(line[j][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j, i, 0);
					else
						num2 = ok_findnum(line, j, i, 0);
				}
				if (ft_isdigit(line[j][i + 1]) && !ft_isdigit(line[j][i]))
				{
					if (!num1)
						num1 = ok_findnum(line, j, i, 0 + 1);
					else
						num2 = ok_findnum(line, j, i, 0 + 1);
				}
				if (ft_isdigit(line[j + 1][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j + 1, i, 0 - 1);
					else
						num2 = ok_findnum(line, j + 1, i, 0 - 1);
				}
				if (ft_isdigit(line[j + 1][i]) && !ft_isdigit(line[j + 1][i - 1]))
				{
					if (!num1)
						num1 = ok_findnum(line, j + 1, i, 0);
					else
						num2 = ok_findnum(line, j + 1, i, 0);
				}
				if (ft_isdigit(line[j + 1][i + 1]) && !ft_isdigit(line[j + 1][i]))
				{
					if (!num1)
						num1 = ok_findnum(line, j + 1, i, 0 + 1);
					else
						num2 = ok_findnum(line, j + 1, i, 0 + 1);
				}
				*ptot += (num1 * num2);
			}
			++i;
		}
		++j;
	}
	j = 0;
	
}

int	main(void)
{
	int 	fd;
	char	*line[142];
	int		i;
	int		j;
	int		total[2];

	i = 0;
	j = 0;
	fd = open("input", O_RDONLY);
	line[0] = 0;
	line[j] = get_next_line(fd);
	total[0] = 0;
	total[1] = 0;
	while (line[j])
	{
		i = ft_strlen(line[j]);
		ft_printf("i = %i\n", i);
		// ok_update(line, &total[0], i, j);
		// ft_printf("t1=%5d\n", total[0]);
		// ok_update2(line, &total[1], i, j);
		// ft_printf("t2=%5d\n", total[1]);
		//free(line);
		++j;
		line[j] = get_next_line(fd);		
	}
	ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	ok_update(line, &total[0], i, j);
	ft_printf("t1=%5d\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5d\n", total[1]);
	close(fd);
	return (0);
}
