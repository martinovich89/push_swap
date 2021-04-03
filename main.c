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
	int		minimum;		//current list minimum
	int		maximum;		//current list maximum
	char	streak;			//0 or 1 ; number sequence continuously increasing or decreasing
	char	direction;		//-1 or 1 ; rolling or reverse-rolling
	char	comp;			//-1 or 1 ; greater or lower comparison
	t_elem	*first;
	t_elem	*last;
	t_elem	*current;
}				t_list;

//////////////////////////////////////
//        GENERAL STRUCTURE         //
//////////////////////////////////////

typedef struct	s_env
{
	int	max;
	int total_numbers;
	char *sequence_str;
	int *numbers;
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
		list->current = list->first;
		list->first = list->first->next;
		free(list->current);
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
		ft_putnbr_fd(env->a_list->current->value, 1);
		env->a_list->current = env->a_list->current->next;
	}
}*/

void	print_lists(t_env *env)
{
	int i;

	env->a_list->current = env->a_list->first;
	env->b_list->current = env->b_list->first;
	i = 0;
	while (i < env->a_list->size || i < env->b_list->size)
	{
		if (i < env->a_list->size)
		{
			ft_putnbr_fd(env->a_list->current->value, 1);
			env->a_list->current = env->a_list->current->next;
		}
		write(1, " ", 1);
		if (i < env->b_list->size)
		{
			ft_putnbr_fd(env->b_list->current->value, 1);
			env->b_list->current = env->b_list->current->next;
		}
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

//////////////////////////////////////
//           CONTRUCTION            //
//////////////////////////////////////

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
	list->current = list->first;
	list->last = list->current;
	set_elem(list->current, env->numbers[i], list->first, list->last);
	list->size++;
	i++;
	while (i < env->total_numbers)
	{
		list->current->next = create_elem();
		set_elem(list->current->next, env->numbers[i], list->first, list->current);
		list->current = list->current->next;
		list->last = list->current;
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

void	push(t_list *dest, t_list *src)
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
}

void	sa(t_env *env)
{
	swap(env->a_list);
	write(1, "sa \n", 4);
	print_lists(env);
}

void	sb(t_env *env)
{
	swap(env->b_list);
	write(1, "sb \n", 4);
	print_lists(env);
}

void	ra(t_env *env)
{
	roll(env->a_list, 1);
	write(1, "ra \n", 4);
	print_lists(env);
}

void	rb(t_env *env)
{
	roll(env->b_list, 1);
	write(1, "rb \n", 4);
	print_lists(env);
}

void	rr(t_env *env)
{
	roll(env->a_list, 1);
	roll(env->b_list, 1);
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
	push(env->a_list, env->b_list);
	write(1, "pa \n", 4);
	print_lists(env);
}

void	pb(t_env *env)
{
	push(env->b_list, env->a_list);
	write(1, "pb \n", 4);
	print_lists(env);
}

//////////////////////////////////////
//        SORTING ALGORITHM         //
//////////////////////////////////////

void	sort_list(t_env *env)
{
	rra(env);
	sa(env);
	rra(env);
	rra(env);
	pb(env);
	pb(env);
	rra(env);
	rra(env);
	pa(env);
	pa(env);
	rra(env);
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
