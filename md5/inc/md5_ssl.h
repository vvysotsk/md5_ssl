/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_ssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:44:38 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:44:40 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_SSL_H
# define MD5_SSL_H
# define BUR_READ 100000
# include "printf.h"

typedef struct		s_word
{
	unsigned char	*word;
	size_t			len;
}					t_word;

typedef struct	s_flags
{
	char	*name;
	void	(*f)(t_word *word, struct s_flags *flags);
	char	r;
	char	q;
	int		p;
	char	b;
	char	ch;
	char	fd_buff;
}				t_flags;

typedef struct	s_md5
{
	char				*name;
	void				(*f)(t_word *word, struct s_flags *flags);
	struct s_md5	*next;
} t_md5;

/**
**	Main functions
**/

void			md5(int ac, char **av, char c_fd);
void			md5_ssl(t_word *word, t_flags *flags);
void			sha256(t_word *word, t_flags *flags);
void			sha224(t_word *word, t_flags *flags);
void			sha512(t_word *word, t_flags *flags);
void			sha384(t_word *word, t_flags *flags);


unsigned int	*md5_cycle(t_word *word, unsigned int *hash_flow,
				int *s_arr, unsigned int *ar_kies);
unsigned int	*sha256_cycle(t_word *word,
	unsigned int *ar_kies, unsigned int *hash_flow);
unsigned int	*init_256ar_kies(void);
unsigned long	ret_val(unsigned long val, int count, int size_b);
int				parse_flags(t_flags *flags, char **av, int ac, int *i);
void			get_fd(t_flags *flags, int fd, char *name);
unsigned long	*sha512_cycle(t_word *word,
	unsigned long *ar_kies, unsigned long *hash_flow);
unsigned long	*init_512ar_kies(void);
t_md5			*init_md5(void);

unsigned long	pif(size_t x, int pow);
size_t	fd_read(int fd, unsigned char **line);
unsigned char	*ft_shunew(size_t len);
void	ft_shtrudel(unsigned char **s);
char	*ft_strupp(char *word);
char	*ft_str_tolower(char *word);
void	ucomp(unsigned char **s1, unsigned char *s2, size_t l1, size_t l2);
#endif
