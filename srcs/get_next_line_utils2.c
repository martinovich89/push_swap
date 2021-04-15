/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 00:03:13 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 00:03:15 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_args_check(t_element *lst, char **line, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
	{
		if (lst && lst->data)
		{
			free(lst->data);
			free(lst);
		}
		return (-1);
	}
	return (0);
}