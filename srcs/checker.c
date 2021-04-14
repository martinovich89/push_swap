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

typedef struct	s_chk
{
	char *inst_list;
}				t_chk;

void	listen_input(t_env *env, t_chk chk)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (chk.inst_list == NULL)
			chk.inst_list = ft_strdup(line);
		else
		{
			tmp = chk.inst_list;
			chk.inst_list = ft_strjoin(chk.inst_list, line);
			free(tmp);
		}
		printf("inst = %s\n", chk.inst_list);
		(void)env;
		free(line);
	}
	free(chk.inst_list);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	t_chk	chk = {};

	if (argc == 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (0);
	if (!(env = create_env()))
		ft_error(env, "error");
	if (parse_args(argc, argv, env) != 0)				// can use an integer to get return value.
		ft_error(env, "error"); // can use parse_args() return value with some error message array.
	make_lists(env);

	printf("Ca marche !!!\n");
	listen_input(env, chk);

    destroy_env(env);
    return (0);
}