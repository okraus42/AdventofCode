/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p8.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:02:42 by okraus            #+#    #+#             */
/*   Updated: 2023/12/08 09:48:03 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>

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



void	ok_update2(char **line, long long *ptot, int i, int j)
{
	char	start[6][4] = {"AAA", "BFA", "VGA", "DXA", "VJA", "BPA"};
	//char	end[6][4] = {"FBZ", "ZZZ", "JVZ", "HRZ", "DGZ", "TMZ"};
	static char	current[6][4];
	char	dir;

	*ptot = 0;
	while (j < 6)
	{
		i = 0;
		while (i < 3)
		{
			current[j][i] = start[j][i];
			++i;
		}
		++j;
	}
	while (current[0][2] != 'Z' || current[1][2] != 'Z' || current[2][2] != 'Z' || current[3][2] != 'Z' || current[4][2] != 'Z' || current[5][2] != 'Z')
	{
		j = 0;
		dir = line[0][*ptot % (ft_strlen(line[0]) - 1)];
		while (j < 6)
		{
			i = 2;
			while (current[j][0] != line[i][0] || current[j][1] != line[i][1] || current[j][2] != line[i][2])
			{
				++i;
			}
			//ft_printf("%i, %s %i %i %s", j, current[j], current[j][0] != line[i][0], (current[j][0] != line[i][0]) || (current[j][1] != line[i][1]) || (current[j][2] != line[i][2]), line[i]);
			if (dir == 'L')
			{
				current[j][0] = line[i][7];
				current[j][1] = line[i][8];
				current[j][2] = line[i][9];
			}
			else
			{
				current[j][0] = line[i][12];
				current[j][1] = line[i][13];
				current[j][2] = line[i][14];
			}
			++j;
			//ft_printf("%i", j);
		}
		*ptot += 1;
		// if (current[0][2] == 'Z' || current[1][2] == 'Z' || current[2][2] == 'Z' || current[3][2] == 'Z' || current[4][2] == 'Z' || current[5][2] == 'Z')
		// {
		// 	ft_printf("%i", *ptot);
		// 	ft_printf("%s %s  %s %s %s %s \n", current[0], current[1], current[2], current[3], current[4], current[5]);
		// }
	}
}

int	main(void)
{
	int 	fd;
	char	*line[1000];
	int		i;
	int		j;
	long long		total[2];

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
		//ft_printf("i = %i\n", i);
		// ok_update(line, &total[0], i, j);
		// ft_printf("t1=%5d\n", total[0]);
		// ok_update2(line, &total[1], i, j);
		// ft_printf("t2=%5d\n", total[1]);
		//free(line);
		++j;
		line[j] = get_next_line(fd);		
	}
	//ft_printf("j = %i\n", j);
	i = 0;
	j = 0;
	//ok_update(line, &total[0], i, j);
	//ft_printf("t1=%5d\n", total[0]);
	ok_update2(line, &total[1], i, j);
	ft_printf("t2=%5lld\n", total[1]);
	close(fd);
	return (0);
}
