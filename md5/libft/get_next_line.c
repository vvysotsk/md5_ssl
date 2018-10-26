/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 01:54:43 by jkrause           #+#    #+#             */
/*   Updated: 2017/10/01 16:12:27 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cat_n(char **src, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	if (!(*src) || src[0][0] == '\0')
		return (0);
	while (src[0][i] && src[0][i] != '\n')
		i++;
	temp = ft_strchr(*src, '\n');
	temp ? temp++ : 0;
	CHECK_NULL((*line = ft_strnew(i)));
	*line = ft_strncpy(*line, *src, i);
	free(*src);
	*src = NULL;
	if (temp)
		CHECK_NULL((*src = ft_strdup(temp)));
	return (1);
}

static t_list	*find_file(t_list *head, size_t fd)
{
	while (head && head->next && head->next->content_size != fd)
		head = head->next;
	if (!head)
	{
		head = (t_list *)malloc(sizeof(t_list));
		head->content_size = fd;
		head->content = NULL;
		head->next = NULL;
		return (head);
	}
	if (!(head->next))
	{
		head->next = (t_list *)malloc(sizeof(t_list));
		head->next->content_size = fd;
		head->next->content = NULL;
		head->next->next = NULL;
	}
	return (head->next);
}

static int		swap_content(int ret, char *t, char **s)
{
	char *temp;

	t[ret] = '\0';
	if (*s)
	{
		temp = ft_strdup(*s);
		free(*s);
		*s = NULL;
		CHECK_NULL((*s = ft_strjoin(temp, t)));
		free(temp);
	}
	else
		CHECK_NULL((*s = ft_strdup(t)));
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*temp_file;
	char			t[BUFF_SIZE + 1];
	int				ret;

	if (read(fd, 0, 0) < 0 || fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	(!head) ? (head = find_file(NULL, fd)) : 0;
	temp_file = find_file(head, fd);
	while ((ret = read(fd, t, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		if (swap_content(ret, t, (char **)(&temp_file->content)) == -1)
			return (-1);
		if (ft_strchr(temp_file->content, '\n'))
			return (ft_cat_n((char **)&(temp_file->content), line));
	}
	return (ft_cat_n((char **)&(temp_file->content), line));
}