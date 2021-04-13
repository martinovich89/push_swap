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

/*

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

#endif

//////////////////////////////////////
//            STRUCTURES            //
//////////////////////////////////////

typedef struct	s_elem
{
	int				value;
	struct s_elem	*next;
	struct s_elem	*prev;
}				t_elem;

typedef struct	s_list
{
	int		size;			//current list size
	int		min;			//current list min
	int		max;			//current list max
	int		streak;
	int		dir;
	int		unsorted;
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
	char	*sequence_str;
	int		*numbers;
	int		min_sort_seq;
	t_list	*a_list;
	t_list	*b_list;
}				t_env;

//////////////////////////////////////
//           DESTRUCTION            //
//////////////////////////////////////

void			destroy_list(t_list *list);
void			destroy_env(t_env *env);

//////////////////////////////////////
//             ERRORS               //
//////////////////////////////////////

void			ft_error(t_env *env, char *str);
long long int	ft_long_atoi(char *str);
int				is_valid_nbr(char *str);
int				is_valid_list(int *tab, int len);
void			print_lists(t_env *env);

//////////////////////////////////////
//           CONTRUCTION            //
//////////////////////////////////////

void			set_list_minmax(t_list *list);
t_elem			*create_elem();
void			set_elem(t_elem *elem, int nb, t_elem *addr1, t_elem *addr2);
t_list			*create_list();
void			array_to_list(t_env *env, t_list *list);
void			make_lists(t_env *env);
void			print_tab(int *tab, int len);
int				multi_arg(int argc, char **argv, t_env *env);
int				single_arg(int argc, char **argv, t_env *env);
int				parse_args(int argc, char **argv, t_env *env);
void			*create_env();

//////////////////////////////////////
//          INSTRUCTIONS            //
//////////////////////////////////////

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

//////////////////////////////////////
//        SORTING ALGORITHM         //
//////////////////////////////////////

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
*/