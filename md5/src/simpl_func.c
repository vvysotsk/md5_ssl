/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpl_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:40:35 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/26 16:40:36 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

char	*ft_strupp(char *word)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(word))
	{
		word[i] = ft_toupper(word[i]);
		i++;
	}
	return (word);
}

void	ft_shtrudel(unsigned char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

unsigned char	*ft_shunew(size_t len)
{
	unsigned char	*res;
	size_t			i;

	res = (unsigned char *)malloc(len + 1);
	i = 0;
	while (i <= len)
	{
		res[i] = '\0';
		i++;
	}
	return(res);
}

size_t	fd_read(int fd, unsigned char **line)
{
	unsigned char	*temp;
	size_t			ret;
	int				i;
	struct stat		st;

 	fstat(fd, &st);
	temp = ft_shunew(st.st_size);
	ret = 0;
	while ((i = read(fd, temp, st.st_size)) > 0)
	{
		ret += i;
		ucomp(line, temp, ret - i, i);
		(temp) ? ft_shtrudel(&temp) : 0;
		temp = ft_shunew(st.st_size);
	}
	(temp) ? ft_shtrudel(&temp) : 0;
	return (ret);
}

unsigned long	pif(size_t x, int pow)
{
	unsigned long res;

	res = 1;
	while (pow > 0)
	{
		res = res * x;
		pow--;
	}
	return (res);
}
