/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 02:59:03 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/13 02:59:04 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct	s_chk
{
	char	**cmd_tab;
	char	*cmd_list;
	char	*tmp;
	int		error;
	int		fd;
}				t_chk;

typedef struct	s_elem
{
	int				value;
	struct s_elem	*next;
	struct s_elem	*prev;
}				t_elem;

typedef struct	s_list
{
	int		size;
	int		min;
	int		max;
	int		streak;
	int		dir;
	int		cell_count;
	int		id;
	t_elem	*start;
	t_elem	*first;
	t_elem	*last;
	t_elem	*cur;
}				t_list;

typedef struct	s_env
{
	int		cmd;
	int		min;
	int		max;
	int		total_numbers;
	int		*numbers;
	t_list	*a_list;
	t_list	*b_list;
}				t_env;

void			destroy_list(t_list *list);
void			destroy_env(t_env *env);
void			destroy_chk(t_chk *chk);

void			ft_error(t_env *env, char *str);
long long int	ft_long_atoi(char *str);
int				is_valid_nbr(char *str);
int				is_valid_list(int *tab, int len);
void			print_lists(t_env *env);
void			ft_chk_error(t_env *env, t_chk *chk);
void			free_and_quit(t_env *env, char **tab, char *str);

void			make_tab(t_env *env, t_chk *chk);
void			set_list_minmax(t_list *list);
t_elem			*create_elem();
void			set_elem(t_elem *elem, int nb, t_elem *addr1, t_elem *addr2);
t_list			*create_list();
void			array_to_list(t_env *env, t_list *list);
void			make_lists(t_env *env);
void			print_tab(int *tab, int len);
int				multi_arg(int argc, char **argv, t_env *env);
int				single_arg(char **argv, t_env *env);
int				parse_args(int argc, char **argv, t_env *env);
t_env			*create_env();

void			swap(t_list *list);
void			roll(t_list *list, int dir);
void			push(t_list *dest, t_list *src);
void			sa(t_env *env);
void			sb(t_env *env);
void			ss(t_env *env);
void			ra(t_env *env);
void			rb(t_env *env);
void			rr(t_env *env);
void			rra(t_env *env);
void			rrb(t_env *env);
void			rrr(t_env *env);
void			pa(t_env *env);
void			pb(t_env *env);

int				is_valid_input_str(char *str);
int				elems_left(t_list *list);
int				is_sorted(t_elem *elem1, t_elem *elem2);
int				streak_len(t_list *list, t_elem *start);
int				rev_streak_len(t_list *list, t_elem *start);
int				set_streak(t_list *list, t_elem *start, int dir);
void			get_next_streak(t_list *list);
int				is_sorted_list(t_env *env, t_list *list);
int				skip_streak(t_list *list);
int				min_streak(t_list *list, t_elem *start);
int				count_cells(t_list *list);
int				skip_seq(t_env *env, t_list *list, int dir);
void			insert_seq(t_env *env);
void			fix_position(t_env *env, t_list *list, int dir);
void			push_cell(t_env *env, t_list *dest, t_list *src);
void			merge_cells(t_env *env, t_list *dest, t_list *src);
void			reverse_seq(t_env *env);
void			push_cells(t_env *env, t_list *dest, t_list *src, int nb);
void			atob(t_env *env);
void			btoa(t_env *env);
void			make_seq(t_env *env);
void			sort_two(t_env *env, t_list *list);
void			sort_three(t_env *env, t_list *list);
void			sort_four(t_env *env, t_list *list);
void			sort_small(t_env *env);
void			make_cells(t_env *env);
void			sorting_algorithm(t_env *env);
void			sort_list(t_env *env);
void			check_sequence(t_env *env);
void			apply_cmd(t_env *env, t_chk *chk);
int				is_valid_input(char *line);
void			append_cmd(t_env *env, t_chk *chk, char *line);
void			get_cmd(t_env *env, t_chk *chk, char *line);
void			listen_input(t_env *env, t_chk *chk);
void			pick_cmd(t_env *env, t_chk *chk, int i);

#endif
