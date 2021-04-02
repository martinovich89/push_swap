/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_uint_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:39:17 by martin            #+#    #+#             */
/*   Updated: 2020/10/16 23:39:19 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_build_tab(int nb)
{
	int	*tab;

	tab = NULL;
	if (!(tab = malloc(sizeof(int) * nb)))
		return (NULL);
	return (tab);
}
