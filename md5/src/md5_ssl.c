/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:38:26 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:38:27 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static int			*init_ar_n(void)
{
	int *ar_n;
	int *buff;
	int i;

	ar_n = (int *)malloc(sizeof(int) * 64);
	buff = (int[64]){7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
					5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
					4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
					6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	i = 0;
	while (i < 64 && ++i)
		ar_n[i - 1] = buff[i - 1];
	return (ar_n);
}

static unsigned int	*init_ar_kies(void)
{
	unsigned int	*ar_kies;
	unsigned int	*buff;
	int				i;

	buff = (unsigned int[64])
	{
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
		0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
		0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
		0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};
	ar_kies = (unsigned int *)malloc(64 * sizeof(unsigned int));
	i = 0;
	while (i < 64 && ++i)
		ar_kies[i - 1] = buff[i - 1];
	return (ar_kies);
}

static unsigned int	*init_hash_flow(void)
{
	unsigned int *hash_flow;

	hash_flow = (unsigned int *)malloc(4 * sizeof(unsigned int));
	hash_flow[0] = 0x67452301;
	hash_flow[1] = 0xefcdab89;
	hash_flow[2] = 0x98badcfe;
	hash_flow[3] = 0x10325476;
	return (hash_flow);
}

static void			print(unsigned int *hash_flow, t_flags *flags)
{
	int i;
	int j;

	i = -1;
	while (++i < 4 && (j = 1))
		while (j < 5)
		{
			if (flags->b == 0)
				ft_printf("%.2x", hash_flow[i] % 256);
			else
				ft_printf("%.8b", hash_flow[i] % 256);
			hash_flow[i] /= 256;
			j++;
		}
}

void				md5_ssl(t_word *word, t_flags *flags)
{
	int				*ar_n;
	unsigned int	*ar_kies;
	unsigned int	*hash_flow;

	ar_n = init_ar_n();
	ar_kies = init_ar_kies();
	hash_flow = init_hash_flow();
	hash_flow = md5_cycle(word, hash_flow, ar_n, ar_kies);
	print(hash_flow, flags);
	free(ar_n);
	free(ar_kies);
	free(hash_flow);
}
