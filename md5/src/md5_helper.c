/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:38:48 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:38:49 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

char	*ft_str_tolower(char *word)
{
	size_t i;

	i = 0;
	while (i < ft_strlen(word))
	{
		word[i] = ft_tolower(word[i]);
		i++;
	}
	return (word);
}

static unsigned int	exort(unsigned int *temp, int i,
	unsigned int *ar_kies, unsigned int *buff_ar)
{
	unsigned int	f;
	int				g;

	g = 0;
	f = 0;
	if (i >= 0 && i <= 15 && (g = i) != -1)
		f = (temp[1] & temp[2]) | ((~temp[1]) & temp[3]);
	if (i >= 16 && i <= 31 && (g = (5 * i + 1) % 16) != -1)
		f = (temp[3] & temp[1]) | ((~temp[3]) & temp[2]);
	if (i >= 32 && i <= 47 && (g = (3 * i + 5) % 16) != -1)
		f = temp[1] ^ temp[2] ^ temp[3];
	if (i >= 48 && i <= 63 && (g = (7 * i) % 16) != -1)
		f = temp[2] ^ (temp[1] | (~temp[3]));
	f = f + temp[0] + ar_kies[i] + buff_ar[g];
	return (f);
}

static void			loop(int *ar_n, unsigned int *ar_kies,
			unsigned int **temp, unsigned int *buff_ar)
{
	int				i;
	unsigned int	f;

	i = 0;
	while (i < 64)
	{
		f = exort(temp[0], i, ar_kies, buff_ar);
		temp[0][0] = temp[0][3];
		temp[0][3] = temp[0][2];
		temp[0][2] = temp[0][1];
		temp[0][1] = temp[0][1] +
		((f << ar_n[i]) | f >> (32 - ar_n[i]));
		i++;
	}
}

static int			init_buff_ar(t_word *word, unsigned int **buff_ar,
	int uno, size_t *counter)
{
	int		i;
	int		k;
	size_t	old;
	size_t	new_len;

	i = -1;
	new_len = word->len / 8 - (*counter);
	old = 0;
	while (++i < 16 && !(k = 0) &&
		!(buff_ar[0][i] = 0))
		while (k < 4 && ++k)
		{
			buff_ar[0][i] = (word->word[0] << (8 * (k - 1))) + buff_ar[0][i];
			(old < new_len && ++old) ? (word->word++) : 0;
		}
	(*counter) += old;
	if (new_len < 64 && uno != 1)
		buff_ar[0][old / 4] += (size_t)pif(2, (old % 4 + 1) * 8 - 1);
	if (new_len < 56)
	{
		buff_ar[0][14] = (unsigned int)word->len % pif(2, 31);
		buff_ar[0][15] = (unsigned int)word->len / pif(2, 31);
		return (2);
	}
	return (new_len < 64);
}

unsigned int		*md5_cycle(t_word *word,
				unsigned int *hash_flow, int *ar_n, unsigned int *ar_kies)
{
	unsigned int	*temp;
	int				i;
	unsigned int	*buff_ar;
	int				check_buff;
	size_t			counter;

	check_buff = 0;
	counter = 0;
	while (check_buff != 2)
	{
		temp = (unsigned int *)malloc(4 * sizeof(unsigned int));
		i = 0;
		while (i < 4 && ++i)
			temp[i - 1] = hash_flow[i - 1];
		buff_ar = (unsigned int *)malloc(16 * sizeof(unsigned int));
		(check_buff = init_buff_ar(word, &buff_ar,
			check_buff, &counter));
		loop(ar_n, ar_kies, &temp, buff_ar);
		i = 0;
		while (i < 4 && ++i)
			hash_flow[i - 1] += temp[i - 1];
		free(temp);
		free(buff_ar);
	}
	return (hash_flow);
}
