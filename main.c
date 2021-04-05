/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:01:05 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/02 00:41:31 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//////////////////////////////////////
//         LIST STRUCTURES          //
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
	int		unsorted;
	t_elem	*start;
	t_elem	*first;
	t_elem	*last;
	t_elem	*cur;
}				t_list;

//////////////////////////////////////
//        GENERAL STRUCTURE         //
//////////////////////////////////////

typedef struct	s_env
{
	int min;
	int	max;
	int total_numbers;
	char *sequence_str;
	int *numbers;
	int min_sort_seq;
	t_list	*a_list;
	t_list	*b_list;
}				t_env;

//////////////////////////////////////
//           DESTRUCTION            //
//////////////////////////////////////

void	destroy_list(t_list *list)
{
	int i;

	i = 0;
	while (i < list->size)
	{
		list->cur = list->first;
		list->first = list->first->next;
		free(list->cur);
		i++;
	}
	free(list);
}

void	destroy_env(t_env *env)
{
	if (env->a_list)
		destroy_list(env->a_list);
	if (env->b_list)
		destroy_list(env->b_list);
	free(env->numbers);
	free(env);
}

//////////////////////////////////////
//             ERRORS               //
//////////////////////////////////////

void	ft_error(t_env *env, char *str)
{
	if (env)
		destroy_env(env);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}

/////////////////////////////////////
//              UTILS              //
/////////////////////////////////////

// Print one elem and go to next. To shorten print_lists().
/*void	print_elem(t_list *list, int i)
{
	if (i < env->a_list->size)
	{
		ft_putnbr_fd(env->a_list->cur->value, 1);
		env->a_list->cur = env->a_list->cur->next;
	}
}*/

void	print_lists(t_env *env)
{
	int i;

	env->a_list->cur = env->a_list->first;
	env->b_list->cur = env->b_list->first;
	i = 0;
	while (i < env->a_list->size || i < env->b_list->size)
	{
		if (i < env->a_list->size)
		{
			ft_putnbr_fd(env->a_list->cur->value, 1);
			env->a_list->cur = env->a_list->cur->next;
		}
		else
			write(1, " ", 1);
		write(1, " ", 1);
		if (i < env->b_list->size)
		{
			ft_putnbr_fd(env->b_list->cur->value, 1);
			env->b_list->cur = env->b_list->cur->next;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

//////////////////////////////////////
//           CONTRUCTION            //
//////////////////////////////////////

void	set_list_minmax(t_list *list)
{
	int i;

	list->cur = list->first;
	list->min = list->cur->value;
	list->max = list->cur->value;
	i = 0;
	while (i < list->size)		// on parcourt la chaine et on set min et max.
	{
		list->cur = list->cur->next;
		if (list->cur->value < list->min)
			list->min = list->cur->value;
		if (list->cur->value > list->max)
			list->max = list->cur->value;
		i++;
	}
}

t_elem	*create_elem()
{
	t_elem *elem;

	elem = NULL;
	if (!(elem = malloc(sizeof(t_elem))))  //can use ft_calloc here
		return (NULL);
	ft_bzero(elem, sizeof(t_elem)); // USE LIBFT FFS !!
	return (elem);
}

void	set_elem(t_elem *elem, int nb, t_elem *addr1, t_elem *addr2)
{
	elem->value = nb;
	elem->next = addr1;
	elem->prev = addr2;
}

t_list	*create_list()
{
	t_list *list;

	list = NULL;
	if (!(list = malloc(sizeof(t_list)))) //can use ft_calloc here
		return (NULL);
	ft_bzero(list, sizeof(t_list)); // USE LIBFT FFS !!
	return (list);
}

// Creation d'une liste bouclee doublement chainee.
void	array_to_list(t_env *env, t_list *list)
{
	int i;

	i = 0;
	list->first = create_elem();
	list->cur = list->first;
	list->last = list->cur;
	set_elem(list->cur, env->numbers[i], list->first, list->last);
	list->size++;
	i++;
	while (i < env->total_numbers)
	{
		list->cur->next = create_elem();
		set_elem(list->cur->next, env->numbers[i], list->first, list->cur);
		list->cur = list->cur->next;
		list->last = list->cur;
		list->first->prev = list->last;
		list->size++;
		i++;
	}
}

void	make_lists(t_env *env)
{
	env->a_list = create_list();
	env->b_list = create_list();
	array_to_list(env, env->a_list);
//	env->b_list->first = create_elem();
//	set_elem(env->b_list->first, 0, env->b_list->first, env->b_list->first);
}

int		parse_args(int argc, char **argv, t_env *env)
{
	int i;

	if (argc < 2)
		return (1);
	if (!(env->numbers = ft_build_tab(argc - 1))) // 1st arg is program name ... 
		return (2);
	i = 1;
	while (i < argc)
	{
		if (!is_charset_str(argv[i], "0123456789"))
			return (3);
		env->numbers[i - 1] = ft_atoi(argv[i]); // argv[1] 1st nb, env->numbers[0] 1st slot
		i++;
	}
	env->total_numbers = argc - 1;
	return (0);
}

void	*create_env()
{
	t_env *env;

    env = NULL;
    if (!(env = malloc(sizeof(t_env)))) //can use ft_calloc here
        return (NULL);
	ft_bzero(env, sizeof(t_env)); // USE LIBFT FFS !!
    return (env);
}

//////////////////////////////////////
//          INSTRUCTIONS            //
//////////////////////////////////////

void	swap(t_list *list)
{
	int tmp;

	tmp = list->first->value;
	list->first->value = list->first->next->value;
	list->first->next->value = tmp;
}

void	roll(t_list *list, int dir)
{
	if (dir > 0)
	{
		list->first = list->first->next;
		list->last = list->last->next;
	}
	else
	{
		list->first = list->first->prev;
		list->last = list->last->prev;
	}
}

/*void	push(t_list *dest, t_list *src)
{
	t_elem *tmp;
	if (src->size >= 1)
	{
//		printf("%p\n%p\n--------------\n", src->first, src->first->next);
		tmp = src->first->next;
//		printf("%p\n%p\n%p\n%p\n--------------\n", tmp, src->first, src->first->next, src->first->prev);
		src->last->next = tmp;
//		printf("%p\n%p\n%p\n%p\n--------------\n", tmp, src->first, src->first->next, src->first->prev);
		src->first->next = dest->first;
//		printf("%p\n%p\n%p\n%p\n--------------\n", tmp, src->first, src->first->next, src->first->prev);
		src->first->prev = dest->last;
//		printf("%p\n%p\n%p\n%p\n--------------\n", tmp, src->first, src->first->next, src->first->prev);
////		src->last->next = tmp;
////		printf("%p\n%p\n%p\n%p\n--------------\n", tmp, src->first, src->first->next, src->first->prev);
		tmp->prev = src->last;
//		printf("%p\n%p\n--------------\n", tmp->prev, src->last);
		dest->first = src->first;
//		printf("%p\n%p\n--------------\n", dest->first, src->first);
		src->first = tmp;
//		printf("%p\n--------------\n", dest->last);
		src->size--;
		dest->size++;
		if (!dest->last)
			dest->last = dest->first;
		dest->last->next = dest->first;
		if (dest->size <= 2)
			dest->last->prev = dest->first;
		
	}
}*/

void    push(t_list *dest, t_list *src)
{
    t_elem *tmp;

    tmp = src->first;
    src->last->next = tmp->next;
    tmp->next->prev = src->last;
    src->first = tmp->next;
    tmp->next = dest->first;
    if(dest->first)
        dest->first->prev = tmp;
    tmp->prev = dest->last;
    if(dest->last)
    	dest->last->next = tmp;
    dest->first = tmp;
    src->size--;
    dest->size++;
    if (!dest->last)
	{ 
        dest->last = dest->first;
        dest->last->prev = dest->first;
        dest->last->next = dest->first;
        dest->first->prev = dest->first;
        dest->first->next = dest->first;
    }
}

void	sa(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		swap(env->a_list);
		write(1, "sa \n", 4);
		print_lists(env);
	}
}

void	sb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		swap(env->b_list);
		write(1, "sb \n", 4);
		print_lists(env);
	}
}

void	ss(t_env *env)
{
	sa(env);
	sb(env);
	write(1, "ss \n", 4);
	print_lists(env);             
}

void	ra(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		roll(env->a_list, 1);
		write(1, "ra \n", 4);
		print_lists(env);
	}
}

void	rb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		roll(env->b_list, 1);
		write(1, "rb \n", 4);
		print_lists(env);
	}
}

void	rr(t_env *env)
{
	ra(env);
	rb(env);
	write(1, "rr \n", 4);
	print_lists(env);
}

void	rra(t_env *env)
{
	roll(env->a_list, -1);
	write(1, "rra \n", 5);
	print_lists(env);
}

void	rrb(t_env *env)
{
	roll(env->b_list, -1);
	write(1, "rrb \n", 5);
	print_lists(env);
}

void	rrr(t_env *env)
{
	roll(env->a_list, -1);
	roll(env->b_list, -1);
	write(1, "rrr \n", 5);
	print_lists(env);
}

void	pa(t_env *env)
{
	if (env->b_list->size >= 1)
    {
		push(env->a_list, env->b_list);
		set_list_minmax(env->a_list);
		set_list_minmax(env->b_list);
		write(1, "pa \n", 4);
		print_lists(env);
	}
}

void	pb(t_env *env)
{
	if (env->a_list->size >= 1)
	{
		push(env->b_list, env->a_list);
		set_list_minmax(env->a_list);
		set_list_minmax(env->b_list);
		write(1, "pb \n", 4);
		print_lists(env);
	}
}

//////////////////////////////////////
//        SORTING ALGORITHM         //
//////////////////////////////////////

int		min_sorted(t_env *env)
{
	int i;
	int	min_streak;
	int	ret;

	ret = 0;
	min_streak = 0;
	i = 0;
	while (i < env->total_numbers)
	{
		if ((ret = set_streak(env->a_list)) < min_streak)
			min_streak
		i++;
	}
}

void	skip_seq(t_env *env)
{
	int i;

	i = 0;
	while (i < env->a_list->streak)
	{
		ra(env);
		i++;
	}
}

// On compare les value pour savoir si elles sont ordonnees. Le min d'une liste est ordonne quand il est apres le max.
int		is_sorted(t_elem *elem1, t_elem *elem2, int nb1, int nb2)
{
	if (elem1->value <= elem2->value || (elem1->value == nb2 && elem2->value == nb1))
		return (1);
	else
		return (0);
}

int		elems_left(t_list *list)
{
	int i;

	i = 0;
	while (list->cur != list->start)
	{
		list->cur = list->cur->next;
		i++;
	}
	return (0);
}

// Parcourt la chaine jusqu'a trouver une discontinuite dans l'ordre. Retourne le nombre de valeurs ordonnees. Positif si dans l'ordre, Negatif si inverse.
int		set_streak(t_list *list, t_elem *start)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < list->size
	&& is_sorted(list->cur, list->cur->next, list->min, list->max)) // && (list->cur->next->value >= list->cur->value || (list->cur->value == list->max && list->cur->next->value == list->min)))
	{
		list->cur = list->cur->next;
		i++;
	}
	list->cur = start;
	while (j < list->size
	&& !is_sorted(list->cur->next, list->cur, list->max, list->min)) // && (list->cur->next->value <= list->cur->value || (list->cur->value == list->min && list->cur->next->value == list->max)))
	{
		list->cur = list->cur->next;
		j--;
	}
	return (i + j);
}

void	sorting_algorithm(t_env *env)
{
	env->a_list->start = env->a_list->first;
	env->a_list->cur = env->a_list->start;
	env->min_sort_seq = 5;
	while (set_streak(env->a_list, env->a_list->cur) != env->total_numbers - 1)
	{
		while (env->a_list->cur->next != env->a_list->start && (min_sorted(env) < env->min_sort_seq || min_sorted(env) == env->total_numbers))
		{
			get_next_streak();
			env->a_list->streak = set_streak(env->a_list, env->a_list->cur); // combien d' elements d'affilee sont tries.
			if (env->a_list->streak >= 4)                                    // si plus de 5 elements sont tries, on passe la sequence.
				skip_seq(env);
			else if (env->a_list->streak < 4 && env->a_list->streak > -4)
				env->a_list->unsorted = set_unsorted();
			else if (env->a_list->streak <= -4)
				reverse_seq(env->a_list);
		}
		insert_last();
		env->min_sort_seq *= 2;
	}
	fix_position(env->a_list);
}

//////////////////////////////////////
//              MAIN                //
//////////////////////////////////////

int main(int argc, char **argv)
{
	t_env	*env;

	if (!(env = create_env()))
		ft_error(env, "error");
	if (parse_args(argc, argv, env) != 0)				// can use an integer to get return value.
		ft_error(env, "error"); // can use parse_args() return value with some error message array.
	else
	{
		make_lists(env);
		sort_list(env);
		write(1, "result : \n", 10);
		print_lists(env);
//		printf("%p\n%p\n%p\n%p\n%p\n%p\n", env->a_list->first, env->a_list->first->next, env->a_list->first->next->next, env->a_list->first->next->next->next, env->a_list->first->next->next->next->next, env->a_list->first->next->next->next->next->next);
		destroy_env(env);
	}

	return (0);
}
