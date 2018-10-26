/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_224.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:39:28 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:39:30 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static unsigned int	*init_sha224(void)
{
	unsigned int *hash_flow;

	hash_flow = (unsigned int *)malloc(8 * sizeof(unsigned int));
	hash_flow[0] = 0xc1059ed8;
	hash_flow[1] = 0x367cd507;
	hash_flow[2] = 0x3070dd17;
	hash_flow[3] = 0xf70e5939;
	hash_flow[4] = 0xffc00b31;
	hash_flow[5] = 0x68581511;
	hash_flow[6] = 0x64f98fa7;
	hash_flow[7] = 0xbefa4fa4;
	return (hash_flow);
}

void				sha224(t_word *word, t_flags *flags)
{
	unsigned int	*ar_kies;
	unsigned int	*hash_flow;
	int				i;

	ar_kies = init_256ar_kies();
	hash_flow = init_sha224();
	hash_flow = sha256_cycle(word, ar_kies, hash_flow);
	i = -1;
	while (++i < 7)
		if (flags->b == 0)
			ft_printf("%.8x", hash_flow[i]);
		else
			ft_printf("%.32b", hash_flow[i]);
	free(ar_kies);
	free(hash_flow);
}
