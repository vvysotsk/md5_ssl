/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_256_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:42:25 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:42:26 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

unsigned int	*init_256ar_kies(void)
{
	unsigned int	*ar_kies;
	unsigned int	*temp;
	int				i;

	ar_kies = (unsigned int *)malloc(64 * sizeof(unsigned int *));
	temp = (unsigned int[64])
	{
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
		0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
		0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
		0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
		0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	i = 0;
	while (i < 64 && ++i)
		ar_kies[i - 1] = temp[i - 1];
	return (ar_kies);
}

static void		get_ar_ui(unsigned int **ar_ui)
{
	int				i;
	unsigned int	s0;
	unsigned int	s1;

	i = 16;
	while (i < 64)
	{
		s0 = ret_val(ar_ui[0][i - 15], 7, 32) ^
			ret_val(ar_ui[0][i - 15], 18, 32) ^ ar_ui[0][i - 15] >> 3;
		s1 = ret_val(ar_ui[0][i - 2], 17, 32) ^
			ret_val(ar_ui[0][i - 2], 19, 32) ^ ar_ui[0][i - 2] >> 10;
		ar_ui[0][i] = ar_ui[0][i - 16] + s0 + ar_ui[0][i - 7] + s1;
		i++;
	}
}

static int		init_ar_ui(t_word *word, unsigned int **ar_ui,
			int uno, size_t *counter)
{
	size_t			new_len;
	int				i;
	int				j;
	size_t			end;

	new_len = word->len / 8 - (*counter);
	i = 0;
	end = 0;
	while (i < 16 && ++i && !(j = 0))
		while (j < 4 && ++j)
		{
			ar_ui[0][i - 1] = (ar_ui[0][i - 1] << 8) + word->word[0];
			(end < new_len && ++end) ? (word->word++) : 0;
		}
	(*counter) += end;
	if (new_len < 64 && uno != 1)
		ar_ui[0][end / 4] +=
					(size_t)pif(2, (4 - end % 4) * 8 - 1);
	if (new_len < 56)
	{
		ar_ui[0][14] = (unsigned int)word->len / pif(2, 31);
		ar_ui[0][15] = (unsigned int)word->len % pif(2, 31);
	}
	get_ar_ui(ar_ui);
	return ((new_len < 64) + (new_len < 56));
}

static void		loop(unsigned int **ar,
	unsigned int *ar_kies, unsigned int *ar_ui)
{
	int				i;
	unsigned int	a;
	unsigned int	b;

	i = 0;
	while (i < 64)
	{
		a = ar[0][7] + (ret_val(ar[0][4], 6, 32) ^
			ret_val(ar[0][4], 11, 32) ^ ret_val(ar[0][4], 25, 32));
		a += ((ar[0][4] & ar[0][5]) ^ (~ar[0][4] & ar[0][6]));
		a += ar_kies[i] + ar_ui[i];
		b = ret_val(ar[0][0], 2, 32) ^ ret_val(ar[0][0], 13, 32) ^
		ret_val(ar[0][0], 22, 32);
		b += (ar[0][0] & ar[0][1]) ^ (ar[0][0] & ar[0][2]) ^
		(ar[0][1] & ar[0][2]);
		ar[0][7] = ar[0][6];
		ar[0][6] = ar[0][5];
		ar[0][5] = ar[0][4];
		ar[0][4] = ar[0][3] + a;
		ar[0][3] = ar[0][2];
		ar[0][2] = ar[0][1];
		ar[0][1] = ar[0][0];
		ar[0][0] = a + b;
		i++;
	}
}

unsigned int	*sha256_cycle(t_word *word,
	unsigned int *ar_kies, unsigned int *hash_flow)
{
	unsigned int	*temp;
	unsigned int	*ar_ui;
	int				i;
	int				check;
	size_t			counter;

	check = 0;
	counter = 0;
	while (check != 2)
	{
		i = 0;
		temp = (unsigned int *)malloc(8 * sizeof(unsigned int));
		while (i < 8 && ++i)
			temp[i - 1] = hash_flow[i - 1];
		ar_ui = (unsigned int *)malloc(64 * sizeof(unsigned int));
		check = init_ar_ui(word, &ar_ui, check,
			&counter);
		loop(&temp, ar_kies, ar_ui);
		i = 0;
		while (i < 8 && ++i)
			hash_flow[i - 1] += temp[i - 1];
		free(temp);
		free(ar_ui);
	}
	return (hash_flow);
}
