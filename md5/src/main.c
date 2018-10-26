/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:37:30 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:37:31 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

void	ucomp(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2)
{
	unsigned char	*temp;
	size_t	i;

	temp = ft_shunew(l1);
	i = 0;
	while (i < l1 && ++i)
		temp[i - 1] = s1[0][i - 1];
	(*s1) ? ft_shtrudel(s1) : 0;
	*s1 = ft_shunew(l1 + l2);
	i = 0;
	while (i < l1 && ++i)
		s1[0][i - 1] = temp[i - 1];
	i = 0;
	while (i < l2 && ++i)
		s1[0][l1 + i - 1] = s2[i - 1];
	ft_shtrudel(&temp);
}



int				main(int ac, char **av)
{
	char	*buff;
	char	**ar_str;
	int		count;
	int		i;

	if (ac < 2)
	{
		ft_printf("ft_ssl>");
		while (get_next_line(0, &buff))
		{
			if ((i = -1) && buff && !ft_strcmp(buff, "exit"))
				exit(0);
			(!(count = 0) && buff) ? ar_str = ft_strsplit(buff, ' ') : 0;
			while (buff && buff[++i])
				if ((buff[i] == ' ' && buff[i + 1] != ' ' && buff[i + 1])
					|| (i == 0 && buff[i] != ' '))
					count++;
			buff[0] ? md5(count, ar_str, 1) : 0;
			ft_strdel(&buff);
			ft_printf("ft_ssl>");
		}
	}
	else
		md5(ac - 1, &av[1], 0);
	return (0);
}
