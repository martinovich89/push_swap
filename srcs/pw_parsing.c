/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pw_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:17:47 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/15 17:17:49 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_and_quit(t_env *env, char **tab, char *str)
{
	free(str);
	ft_tabdel(tab);
	ft_error(env, "Error");
}

int		multi_arg(int argc, char **argv, t_env *env)
{
	int i;

	if (env->numbers == NULL)
		if (!(env->numbers = ft_build_tab(argc - 1)))
			return (2);
	i = 1;
	while (i < argc)
	{
		if (!is_charset_str(argv[i], "-0123456789"))
			return (3);
		if (!is_valid_nbr(argv[i]))
			return (4);
		env->numbers[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	env->total_numbers = argc - 1;
	return (0);
}

int		single_arg(char **argv, t_env *env)
{
	char **tab;
	char *str;
	char *tmp;

	if (!(str = ft_strjoin(argv[0], " ")))
		return (2);
	tmp = str;
	if (!(str = ft_strjoin(str, argv[1])))
	{
		free(tmp);
		free(str);
		return (2);
	}
	free(tmp);
	if (!(tab = ft_split(str, ' ')))
	{
		free(str);
		return (2);
	}
	if (multi_arg((ft_tablen(tab)), tab, env))
		free_and_quit(env, tab, str);
	ft_tabdel(tab);
	free(str);
	tab = NULL;
	return (0);
}

int		parse_args(int argc, char **argv, t_env *env)
{
	if (argc < 2)
		return (1);
	if (argc == 2 && argv[1][0] == '\0')
		ft_error(env, "Error");
	else if (argc == 2 && is_charset_str(argv[1], "- 1234567890") &&
	!is_valid_input_str(argv[1]))
		ft_error(env, "Error");
	else if (argc == 2)
	{
		if (single_arg(argv, env))
			ft_error(env, "Error");
	}
	else
	{
		if (multi_arg(argc, argv, env))
			ft_error(env, "Error");
	}
	if (!is_valid_list(env->numbers, env->total_numbers))
		ft_error(env, "Error");
	return (0);
}
