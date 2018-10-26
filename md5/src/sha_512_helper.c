/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha_512_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:43:16 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:43:18 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static void		exort(unsigned long **ar_ul)
{
	int				i;
	unsigned long	val1;
	unsigned long	val2;

	i = 16;
	while (i < 80)
	{
		val1 = ret_val(ar_ul[0][i - 15], 1, 64) ^
			ret_val(ar_ul[0][i - 15], 8, 64) ^ ar_ul[0][i - 15] >> 7;
		val2 = ret_val(ar_ul[0][i - 2], 19, 64) ^
			ret_val(ar_ul[0][i - 2], 61, 64) ^ ar_ul[0][i - 2] >> 6;
		ar_ul[0][i] = ar_ul[0][i - 16] + val1 + ar_ul[0][i - 7] + val2;
		i++;
	}
}

static int		init_ar_ul(t_word *word, unsigned long **ar_ul,
		int uno, size_t *counter)
{
	unsigned long	new_len;
	int				i;
	int				k;
	size_t			end;

	new_len = word->len / 8 - (*counter);
	i = 0;
	end = 0;
	while (i < 16 && ++i && !(k = 0))
		while (k < 8 && ++k)
		{
			ar_ul[0][i - 1] = (ar_ul[0][i - 1] << 8) + word->word[0];
			(end < new_len && ++end) ? (word->word++) : 0;
		}
	(*counter) += end;
	if (new_len < 128 && uno != 1)
		ar_ul[0][end / 8] += pif(2, (8 - end % 8) * 8 - 1);
	if (new_len < 112)
	{
		ar_ul[0][14] = word->len / pif(2, 63);
		ar_ul[0][15] = word->len % pif(2, 63);
	}
	exort(ar_ul);
	return ((new_len < 128) + (new_len < 112));
}

static void		loop(unsigned long **temp,
	unsigned long *ar_kies, unsigned long *ar_ul)
{
	int				i;
	unsigned long	temp1;
	unsigned long	temp2;

	i = 0;
	while (i < 80)
	{
		temp1 = temp[0][7] + (ret_val(temp[0][4], 14, 64) ^
			ret_val(temp[0][4], 18, 64) ^ ret_val(temp[0][4], 41, 64));
		temp1 += ((temp[0][4] & temp[0][5]) ^ (~temp[0][4] & temp[0][6]));
		temp1 += ar_kies[i] + ar_ul[i];
		temp2 = ret_val(temp[0][0], 28, 64) ^ ret_val(temp[0][0], 34, 64) ^
		ret_val(temp[0][0], 39, 64);
		temp2 += (temp[0][0] & temp[0][1]) ^ (temp[0][0] & temp[0][2]) ^
		(temp[0][1] & temp[0][2]);
		temp[0][7] = temp[0][6];
		temp[0][6] = temp[0][5];
		temp[0][5] = temp[0][4];
		temp[0][4] = temp[0][3] + temp1;
		temp[0][3] = temp[0][2];
		temp[0][2] = temp[0][1];
		temp[0][1] = temp[0][0];
		temp[0][0] = temp1 + temp2;
		i++;
	}
}

unsigned long	*sha512_cycle(t_word *word,
	unsigned long *ar_kies, unsigned long *hash_flow)
{
	unsigned long	*buff;
	unsigned long	*ar_ul;
	int				i;
	int				check;
	size_t			counter;

	check = 0;
	counter = 0;
	while (check != 2)
	{
		i = 0;
		buff = (unsigned long *)malloc(8 * sizeof(unsigned long));
		while (i < 8 && ++i)
			buff[i - 1] = hash_flow[i - 1];
		ar_ul = (unsigned long *)malloc(80 * sizeof(unsigned long));
		check = init_ar_ul(word, &ar_ul, check,
					&counter);
		loop(&buff, ar_kies, ar_ul);
		i = 0;
		while (i < 8 && ++i)
			hash_flow[i - 1] += buff[i - 1];
		free(buff);
		free(ar_ul);
	}
	return (hash_flow);
}
