/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_ssl_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:39:05 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:39:07 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static t_flags	*init_flag(void (*f)(t_word *word, t_flags *flags),
	char *name)
{
	t_flags *flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->f = f;
	flags->name = ft_strdup(name);
	flags->q = 0;
	flags->r = 0;
	flags->p = 0;
	flags->ch = 0;
	flags->b = 0;
	flags->ch = 0;
	return (flags);
}

static int		put_error(t_md5 **head, char *name)
{
	t_md5 *temp;

	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandart \
commands:\n\nMessage Digest commands:\n", name);
	temp = *head;
	while (temp->name != NULL)
	{
		ft_printf("%s\n", temp->name);
		temp = temp->next;
	}
	ft_printf("\nCipher commands:\n\n");
	while ((*head)->name != NULL)
	{
		temp = (*head)->next;
		ft_strdel(&((*head)->name));
		free(*head);
		*head = temp;
	}
	free(*head);
	return (0);
}

static void		step_in(int i, char **av, int ac, t_flags *flags)
{
	int fd;

	while (i < ac && ++flags->ch)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0 || read(fd, 0, 0) < 0)
			ft_printf("%s: %s: %s\n",
			ft_str_tolower(flags->name), av[i], strerror(errno));
		else
			get_fd(flags, fd, av[i]);
		i++;
		close(fd);
	}
}

static void		parse_proc(t_flags *flags, char **av, int ac)
{
	int i;
	int check;

	i = 0;
	while (++i < ac)
		if (av[i][0] == '-' && av[i][1])
		{
			check = parse_flags(flags, av, ac, &i);
			if (check == -1)
				exit(0);
			if (check == -2)
				return ;
		}
		else
		{
			step_in(i, av, ac, flags);
			break;
		}
	if (flags->ch == 0 && (flags->p == 0 || flags->q
		|| flags->r))
		get_fd(flags, 0, NULL);
}

void			md5(int ac, char **av, char c_fd)
{
	t_flags	*flags;
	t_md5	*core;
	t_md5	*buff;

	core = init_md5();
	buff = core;
	while (buff->name != NULL && ft_strcmp(av[0], buff->name))
		buff = buff->next;
	if (buff->name == NULL && !(put_error(&core, av[0])) && !c_fd)
		exit(0);
	if (buff->name == NULL)
		return ;
	flags = init_flag(buff->f, buff->name);
	flags->fd_buff = c_fd;
	while (core != NULL)
	{
		buff = core->next;
		ft_strdel(&core->name);
		free(core);
		core = buff;
	}
	parse_proc(flags, av, ac);
	ft_strdel(&flags->name);
	free(flags);
}