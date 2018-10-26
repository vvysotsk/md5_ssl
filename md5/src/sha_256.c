/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_256.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:39:40 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:39:43 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

unsigned long		ret_val(unsigned long val, int count, int size_b)
{
	return ((val >> count) | (val << (size_b - count)));
}

static unsigned int	*init_sha256(void)
{
	unsigned int *hash_flow;

	hash_flow = (unsigned int *)malloc(8 * sizeof(unsigned int));
	hash_flow[0] = 0x6a09e667;
	hash_flow[1] = 0xbb67ae85;
	hash_flow[2] = 0x3c6ef372;
	hash_flow[3] = 0xa54ff53a;
	hash_flow[4] = 0x510e527f;
	hash_flow[5] = 0x9b05688c;
	hash_flow[6] = 0x1f83d9ab;
	hash_flow[7] = 0x5be0cd19;
	return (hash_flow);
}

void				sha256(t_word *word, t_flags *flags)
{
	unsigned int	*ar_kies;
	unsigned int	*hash_flow;
	int				i;

	ar_kies = init_256ar_kies();
	hash_flow = init_sha256();
	hash_flow = sha256_cycle(word, ar_kies, hash_flow);
	i = -1;
	while (++i < 8)
		if (flags->b == 0)
			ft_printf("%.8x", hash_flow[i]);
		else
			ft_printf("%.32b", hash_flow[i]);
	free(ar_kies);
	free(hash_flow);
}
