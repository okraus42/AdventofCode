/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:57:35 by okraus            #+#    #+#             */
/*   Updated: 2023/12/02 06:41:56 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_cubes
{
	int	red;
	int	green;
	int	blue;
	int	mr;
	int	mg;
	int	mb;
}	t_cubes;


void	ok_update(char *str, int *ptot, int i, int j)
{
	t_cubes	cubes;
	char	**split;
	int		num;
	int		id;

	id = 0;
	i = 0;
	cubes.red = 0;
	cubes.blue = 0;
	cubes.green = 0;
	while(str[i] && str[i] != ':')
	{
		if (!id && ft_isdigit(str[i]))
		{
			id = ft_atoi(&str[i]);
		}
		++i;
	}
	if (str[i])
		++i;
	split = ft_split(&str[i], ';');
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!num && ft_isdigit(split[i][j]))
			{
				num = ft_atoi(&split[i][j]);
			}
			else if (num && !ft_isdigit(split[i][j]))
			{
				if (!ft_strncmp(&split[i][j], "blue", 4))
				{
					cubes.blue = num;
					num = 0;
				}
				else if (!ft_strncmp(&split[i][j], "red", 3))
				{
					cubes.red = num;
					num = 0;
				}
				else if (!ft_strncmp(&split[i][j], "green", 5))
				{
					cubes.green = num;
					num = 0;
				}
			}
			++j;
			
		}
		ft_printf("r %3i, g %3i, b %3i\n", cubes.red, cubes.green, cubes.blue);
		if (cubes.red > 12 || cubes.green > 13 || cubes.blue > 14)
		{
			ft_free_split(&split);
			return ;
		}
		++i;
	}
	ft_free_split(&split);
	*ptot += id;
}

void	ok_update2(char *str, int *ptot, int i, int j)
{
	t_cubes	cubes;
	char	**split;
	int		num;
	int		id;

	id = 0;
	i = 0;
	cubes.red = 0;
	cubes.blue = 0;
	cubes.green = 0;
	cubes.mr = 0;
	cubes.mg = 0;
	cubes.mb = 0;
	while(str[i] && str[i] != ':')
	{
		if (!id && ft_isdigit(str[i]))
		{
			id = ft_atoi(&str[i]);
		}
		++i;
	}
	if (str[i])
		++i;
	split = ft_split(&str[i], ';');
	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!num && ft_isdigit(split[i][j]))
			{
				num = ft_atoi(&split[i][j]);
			}
			else if (num && !ft_isdigit(split[i][j]))
			{
				if (!ft_strncmp(&split[i][j], "blue", 4))
				{
					cubes.blue = num;
					num = 0;
				}
				else if (!ft_strncmp(&split[i][j], "red", 3))
				{
					cubes.red = num;
					num = 0;
				}
				else if (!ft_strncmp(&split[i][j], "green", 5))
				{
					cubes.green = num;
					num = 0;
				}
			}
			++j;
			
		}
		ft_printf("r %3i, g %3i, b %3i\n", cubes.red, cubes.green, cubes.blue);
		if (cubes.red > cubes.mr)
			cubes.mr = cubes.red;
		if (cubes.blue > cubes.mb)
			cubes.mb = cubes.blue;
		if (cubes.green > cubes.mg)
			cubes.mg = cubes.green;
		
		++i;
	}
	ft_free_split(&split);
	ft_printf("mr %3i, mg %3i, mb %3i\n", cubes.mr, cubes.mg, cubes.mb);
	*ptot += (cubes.mg * cubes.mr * cubes.mb);
}


int	main(void)
{
	int 	fd;
	char	*line;
	int		i;
	int		j;
	int		total[2];

	i = 0;
	j = 0;
	fd = open("input", O_RDONLY);
	line = get_next_line(fd);
	total[0] = 0;
	total[1] = 0;
	while (line)
	{
		ft_printf("%s", line);
		ok_update(line, &total[0], i, j);
		ft_printf("t1=%5d\n", total[0]);
		ok_update2(line, &total[1], i, j);
		ft_printf("t2=%5d\n", total[1]);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
