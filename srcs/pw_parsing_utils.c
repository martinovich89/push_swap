/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pw_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:27:01 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 23:27:03 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		is_valid_list(int *tab, int len)
{
	int i;
	int j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (tab[i] == tab[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		is_valid_nbr(char *str)
{
	size_t			i;
	long long int	check_ovf;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '-' && (i != 0 || str[i + 1] == '\0'))
			return (0);
		if (ft_strlen(str) > 12)
			return (0);
		check_ovf = ft_long_atoi(str);
		if (check_ovf > 2147483647 || check_ovf < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

int		is_valid_input_str(char *str)
{
	int i;
	int len;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (is_in_str("0123456789", str[i]))
			return (1);
		i++;
	}
	return (0);
}
