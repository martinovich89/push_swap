/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:50:35 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/12 10:50:45 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	listen_input(t_env *env)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (ft_strcmp(str, "end") != 0)
	{
		i++;
		(void)env;
	}
}

int		main(int argc, char **argv)
{
	t_env	*env;

	if (argc == 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (0);
	if (!(env = create_env()))
		ft_error(env, "error");
	if (parse_args(argc, argv, env) != 0)				// can use an integer to get return value.
		ft_error(env, "error"); // can use parse_args() return value with some error message array.
	make_lists(env);

//	listen_input(env);

    destroy_env(env);
    return (0);
}