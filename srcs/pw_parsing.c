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
	{
		free(str);
		ft_tabdel(tab);
		ft_error(env, "error");
	}
	ft_tabdel(tab);
	free(str);
	tab = NULL;
	return (0);
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

int		parse_args(int argc, char **argv, t_env *env)
{
	if (argc < 2)
		return (1);	
	else if (argc == 2)
	{
		if (single_arg(argv, env))
			ft_error(env, "error");
	}
	else
	{
		if (multi_arg(argc, argv, env))
			ft_error(env, "error");
	}
	if (!is_valid_list(env->numbers, env->total_numbers))
		ft_error(env, "error");
	return (0);
}
