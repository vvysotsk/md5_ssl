/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:37:55 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/24 16:37:56 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5_ssl.h"

static void	create_crypt(t_md5 **core, char *name,
	void (*f)(t_word *word, t_flags *flags))
{
	t_md5 *temp;

	temp = (t_md5 *)malloc(sizeof(t_md5));
	temp->f = f;
	temp->name = ft_strdup(name);
	temp->next = *core;
	*core = temp;
}

t_md5		*init_md5(void)
{
	t_md5 *core;

	core = NULL;
	create_crypt(&core, NULL, NULL);
	create_crypt(&core, "md5", md5_ssl);
	create_crypt(&core, "sha224", sha224);
	create_crypt(&core, "sha256", sha256);
	create_crypt(&core, "sha384", sha384);
	create_crypt(&core, "sha512", sha512);
	return (core);
}
