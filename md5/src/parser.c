/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:38:07 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:38:08 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static t_word	*init_word(unsigned char *word, size_t length)
{
	t_word	*new;

	new = (t_word *)malloc(sizeof(t_word));
	new->word = word;
	new->len = length * 8;
	return (new);
}

static void		parse_word(t_flags *flags, char **av, int *i, int *k)
{
	t_word *temp;

	if (av[*i][*k + 1])
	{
		if (!flags->q && !flags->r)
			ft_printf("%s (\"%s\") = ", ft_strupp(flags->name),
				&av[*i][*k + 1]);
		temp = init_word((unsigned char *)&av[*i][*k + 1], ft_strlen(&av[*i][*k + 1]));
		flags->f(temp, flags);
		if (!flags->q && flags->r)
			ft_printf(" \"%s\"", &av[*i][*k + 1]);
		*k = *k + (int)ft_strlen(&av[*i][*k + 1]);
	}
	else
	{
		temp = init_word((unsigned char *)av[++(*i)], ft_strlen(av[*i]));
		if (!flags->q && !flags->r)
			ft_printf("%s (\"%s\") = ", ft_strupp(flags->name), av[*i]);
		flags->f(temp, flags);
		if (!flags->q && flags->r)
			ft_printf(" \"%s\"", av[*i]);
		(*k) = (int)ft_strlen(av[*i]) - 1;
	}
	free(temp);
	ft_printf("\n");
}

void			get_fd(t_flags *flags, int fd, char *name)
{
	unsigned char	*ar_str;
	size_t	len;
	t_word	*temp;

	(fd != 0 && !flags->r && !flags->q) ?
			ft_printf("%s (%s) = ", ft_strupp(flags->name), name) : 0;
	if (fd == 0 && flags->p > 1)
	{
		temp = init_word((unsigned char *)"", 0);
		flags->f(temp, flags);
		ft_printf("\n");
		free(temp);
		return ;
	}
	ar_str = ft_shunew(0);
	len = fd_read(fd, &ar_str);
	(fd == 0 && flags->p) ? (ft_printf("%s", ar_str)) : 0;
	temp = init_word(ar_str, len);
	flags->f(temp, flags);
	(fd != 0 && flags->r && !flags->q) ? ft_printf(" %s", name) : 0;
	ft_printf("\n");
	free(temp);
	ft_shtrudel(&ar_str);
}

int				parse_flags(t_flags *flags, char **av, int ac, int *i)
{
	int k;

	k = 0;
	while (++k && av[*i][k])
	{
		if (av[*i][k] != 's' && av[*i][k] != 'q' &&
			av[*i][k] != 'r' && av[*i][k] != 'p' && av[*i][k] != 'b')
		{
			ft_printf("%s: illegal option -- %c\nAvailable flags:\n-p: echo STD\
IN to STDOUT and append cheksum to STDOUT\n-q: quiet mode\n-r: reverse format\n\
-s: print the sum of a string\n-b: print in binary\n", flags->name, av[*i][k]);
			if (!flags->fd_buff)
				return (-1);
			else
				return (-2);
		}
		(av[*i][k] == 'q') ? flags->q = 1 : 0;
		(av[*i][k] == 'r') ? flags->r = 1 : 0;
		(av[*i][k] == 'b') ? flags->b = 1 : 0;
		(av[*i][k] == 'p' && ++flags->p) ? get_fd(flags, 0, NULL) : 0;
		if (av[*i][k] == 's' && (flags->ch = 1))
			(*i == ac - 1 && !av[*i][k + 1]) ? (ft_printf("%s: option requires \
an argument -- s\n", flags->name)) : parse_word(flags, av, i, &k);
	}
	return (0);
}
