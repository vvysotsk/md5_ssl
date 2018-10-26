/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_384.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:42:44 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:42:45 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static unsigned long	*init_sha384(void)
{
	unsigned long *hash_flow;

	hash_flow = (unsigned long *)malloc(8 * sizeof(unsigned long));
	hash_flow[0] = 0xcbbb9d5dc1059ed8;
	hash_flow[1] = 0x629a292a367cd507;
	hash_flow[2] = 0x9159015a3070dd17;
	hash_flow[3] = 0x152fecd8f70e5939;
	hash_flow[4] = 0x67332667ffc00b31;
	hash_flow[5] = 0x8eb44a8768581511;
	hash_flow[6] = 0xdb0c2e0d64f98fa7;
	hash_flow[7] = 0x47b5481dbefa4fa4;
	return (hash_flow);
}

void					sha384(t_word *word, t_flags *flags)
{
	unsigned long	*ar_kies;
	unsigned long	*hash_flow;
	int				i;

	ar_kies = init_512ar_kies();
	hash_flow = init_sha384();
	hash_flow = sha512_cycle(word, ar_kies, hash_flow);
	i = -1;
	while (++i < 6)
		if (flags->b == 0)
			ft_printf("%.16lx", hash_flow[i]);
		else
			ft_printf("%.64lb", hash_flow[i]);
	free(ar_kies);
	free(hash_flow);
}
