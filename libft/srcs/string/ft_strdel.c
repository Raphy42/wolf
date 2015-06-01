/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:37:05 by rdantzer          #+#    #+#             */
/*   Updated: 2014/11/12 16:08:33 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = 0;
	}
}
