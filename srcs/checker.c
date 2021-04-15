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
	char	**cmd_tab;
	char	*cmd_list;
	char	*tmp;
	int		error;
	int		fd;
}				t_chk;

void	destroy_chk(t_chk *chk)
{
	if (chk->cmd_list)
	{
		free(chk->cmd_list);
		chk->cmd_list = NULL;
	}
	if (chk->tmp)
	{
		free(chk->tmp);
		chk->tmp = NULL;
	}
	if (chk->cmd_tab)
	{
		ft_tabdel(chk->cmd_tab);
		chk->cmd_tab = NULL;
	}
}

void	ft_chk_error(t_env *env, t_chk *chk)
{
	destroy_chk(chk);
	ft_error(env, "error");
}

int		is_valid_input(char *line)
{
	size_t i;

	i = 0;
	if (!ft_strcmp(line, "sa") || !ft_strcmp(line, "sb") ||
	!ft_strcmp(line, "ss") || !ft_strcmp(line, "ra") ||
	!ft_strcmp(line, "rb") || !ft_strcmp(line, "rr") ||
	!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrb") ||
	!ft_strcmp(line, "rrr") || !ft_strcmp(line, "pa") ||
	!ft_strcmp(line, "pb"))
		return (1);
	return (0);
}

void	append_cmd(t_env *env, t_chk *chk, char *line)
{
	chk->tmp = chk->cmd_list;
	if (!(chk->cmd_list = ft_strjoin(chk->cmd_list, " ")))
		ft_chk_error(env, chk);
	free(chk->tmp);
	chk->tmp = NULL;
	chk->tmp = chk->cmd_list;
	if (!(chk->cmd_list = ft_strjoin(chk->cmd_list, line)))
		ft_chk_error(env, chk);
	free(chk->tmp);
	chk->tmp = NULL;
}

void	get_cmd(t_env *env, t_chk *chk, char *line)
{
	chk->tmp = line;
	if (is_valid_input(line))
	{
		if (chk->cmd_list == NULL)
		{
			if (!(chk->cmd_list = ft_strdup(line)))
				ft_chk_error(env, chk);
		}
		else
			append_cmd(env, chk, line);
	}
	else
	{
		get_next_line(-1, &line);
		ft_chk_error(env, chk);
	}
	free(line);
	line = NULL;
	chk->tmp = NULL;
}

void	listen_input(t_env *env, t_chk *chk)
{
	char	*line;

	line = NULL;
	while (get_next_line(chk->fd, &line) > 0)
		get_cmd(env, chk, line);
	if (line)
	{
		if (line[0] == '\0' && chk->cmd_list == NULL)
			chk->cmd_list = ft_strdup("");
		free(line);
		line = NULL;
	}
}

void	pick_cmd(t_env *env, t_chk *chk, int i)
{
	if (!ft_strcmp(chk->cmd_tab[i], "sa"))
		sa(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "sb"))
		sb(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "ss"))
		ss(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "ra"))
		ra(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "rb"))
		rb(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "rr"))
		rr(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "rra"))
		rra(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "rrb"))
		rrb(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "rrr"))
		rrr(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "pa"))
		pa(env);
	else if (!ft_strcmp(chk->cmd_tab[i], "pb"))
		pb(env);
}

void	apply_cmd(t_env *env, t_chk *chk)
{
	int i;

	i = 0;
	while (chk->cmd_tab[i])
	{
		pick_cmd(env, chk, i);
		i++;
	}
}

void	make_tab(t_env *env, t_chk *chk)
{
	if (!(chk->cmd_tab = ft_split(chk->cmd_list, ' ')))
		ft_chk_error(env, chk);
}

void	check_sequence(t_env *env)
{
	if (is_sorted_list(env, env->a_list) == 0 && env->a_list->size == env->total_numbers && env->a_list->first->value == env->min)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int		main(int argc, char **argv)
{
	t_env	*env;
	t_chk	chk;
	
	chk = (t_chk){};
	if (argc == 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (0);
	if (argc == 2 && is_charset_str(argv[1], "- 1234567890") &&
	!is_valid_input_str(argv[1]))
		return (0);
	if (!(env = create_env()))
		ft_error(env, "error");
	if (parse_args(argc, argv, env) != 0)
		ft_error(env, "error");
	make_lists(env);
	listen_input(env, &chk);
	make_tab(env, &chk);
	apply_cmd(env, &chk);
//	print_lists(env);
	check_sequence(env);
    destroy_env(env);
	destroy_chk(&chk);
    return (0);
}