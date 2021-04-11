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
	int		dir;
	int		unsorted;
	int		cell_count;
	int		id;
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
	env->a_list->id = 1;
	env->b_list = create_list();
	env->b_list->id = 2;
	array_to_list(env, env->a_list);
	set_list_minmax(env->a_list);
	env->min = env->a_list->min;
	env->max = env->a_list->max;
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

void	set_env_minmax(t_env *env);

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

void    push(t_list *dest, t_list *src)
{
    t_elem *tmp;

    tmp = src->first;
    src->last->next = tmp->next;
    tmp->next->prev = src->last;
    src->first = tmp->next;
	if (!dest->size)
		dest->first = tmp;
	tmp->next = dest->first;
    if(dest->first)
        dest->first->prev = tmp;
	if (!dest->size)
		dest->last = dest->first;
    tmp->prev = dest->last;
    if(dest->last)
    	dest->last->next = tmp;
    dest->first = tmp;
    src->size--;
    dest->size++;
    if (!dest->size)
	{ 
        dest->last = dest->first;
        dest->last->prev = dest->first;
        dest->last->next = dest->first;
        dest->first->prev = dest->first;
        dest->first->next = dest->first;
    }
}

/*void    push(t_list *dest, t_list *src)
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
}*/

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
	if (env->a_list->size >= 2)
		roll(env->a_list, 1);
	if (env->b_list->size >= 2)
		roll(env->b_list, 1);
	if (env->a_list->size >= 2 || env->b_list->size >= 2)
		write(1, "rr \n", 4);
	print_lists(env);
}

void	rra(t_env *env)
{
	if (env->a_list->size >= 2)
	{
		roll(env->a_list, -1);
		write(1, "rra \n", 5);
		print_lists(env);
	}
}

void	rrb(t_env *env)
{
	if (env->b_list->size >= 2)
	{
		roll(env->b_list, -1);
		write(1, "rrb \n", 5);
		print_lists(env);
	}
}

void	rrr(t_env *env)
{
	if (env->a_list->size >= 2)
		roll(env->a_list, -1);
	if (env->b_list->size >= 2)
		roll(env->b_list, -1);
	if (env->a_list->size >= 2 || env->b_list->size >= 2)
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

int		elems_left(t_list *list)
{
	int i;

	i = 0;
	list->cur = list->first;
	while (list->cur->next != list->start)
	{
		list->cur = list->cur->next;
		i++;
	}
	return (i);
}

// On compare les value pour savoir si elles sont ordonnees. Le min d'une liste est ordonne quand il est apres le max.
int		is_sorted(t_elem *elem1, t_elem *elem2)
{
	if (elem1->value <= elem2->value)
		return (1);
	else
		return (0);
}

int		streak_len(t_list *list, t_elem *start)
{
	int i;

	i = 0;
	list->cur = start;
	while (is_sorted(list->cur, list->cur->next) && i < list->size)
	{
		list->cur = list->cur->next;
		i++;
	}
	list->cur = start;
	while (!is_sorted(list->cur, list->cur->next) && -i < list->size)
	{
		list->cur = list->cur->next;
		i--;
	}
	return (i);
}
// TROUVER MOYEN DE MERGE LES DEUX FONCTIONS !!
int		rev_streak_len(t_list *list, t_elem *start)
{
	int i;

	i = 0;
	list->cur = start;
	while (is_sorted(list->cur->prev, list->cur) && i < list->size)
	{
		list->cur = list->cur->prev;
		i++;
	}
	list->cur = start;
	while (!is_sorted(list->cur->prev, list->cur) && -i < list->size)
	{
		list->cur = list->cur->prev;
		i--;
	}
	return (i);
}

int		set_streak(t_list *list, t_elem *start, int dir)
{
	int i;

	i = 0;
	list->cur = start;
	if (dir == 1)
		i = streak_len(list, start);
	else if (dir == -1)
		i = rev_streak_len(list, start);
	list->streak = i;
	return (i);
}

void	get_next_streak(t_list *list)
{
	t_elem	*tmp;
	int		cmp;
	int		cmp_sign;

	tmp = list->cur;  // Utilisation de tmp pour save current avant set_streak().
	cmp = set_streak(list, tmp, 1);
	set_streak(list, tmp, -1);
	cmp_sign = cmp;
	cmp = (cmp < 0) ? -cmp : cmp;
	list->cur = tmp;
	if ((cmp_sign > 0 && list->streak > 0) || (cmp_sign < 0 && list->streak < 0))
	{
		while (cmp-- >= 0)
			list->cur = list->cur->next;
	}
	else
	{
		while (cmp-- > 0 && (list->streak > 1 || list->streak < -1))
			list->cur = list->cur->next;
	}
}

int		is_sorted_list(t_env *env, t_list *list)
{

	int i;

	list->cur = list->first;
//	get_next_streak(list);
	i = 0;
	while (i < env->total_numbers && ((is_sorted(list->cur, list->cur->next) || (list->cur->value == env->max && list->cur->next->value == env->min))))
	{
		list->cur = list->cur->next;
		i++;
	}
	return (i - env->total_numbers); // renvoie 0 si ok, renvoie autre chose si ko.
}

int		skip_streak(t_list *list)
{
	int count;

	count = 0;
	while (is_sorted(list->cur, list->cur->next))
	{
		list->cur = list->cur->next;
		count++;
	}
	if (!is_sorted(list->cur, list->cur->next))
		list->cur = list->cur->next;
	return (count);
}

// Cette fonction renvoie la permiere serie de moins de 5. Sinon, renvoie la plus petite serie.
int		min_streak(t_list *list, t_elem *start)
{
	int		ret;
	int		cmp;

	cmp = 0;
	while (list->cur != start || cmp == 0)
	{
		ret = skip_streak(list);
//		printf("ret = %i\n", ret);
		if (cmp == 0)
			cmp = ret;
		if (ret < 4)
			return (ret);
		cmp = (ret < cmp) ? ret : cmp;
	}
	return (cmp);
}

int		count_cells(t_list *list)
{
	int		count;
	t_elem	*tmp;

	count = 0;
	list->cur = list->first;
	if (list->size == 0)
		return (0);
	get_next_streak(list);
	tmp = list->cur;
	list->cur = list->cur->next;
	while (list->cur != tmp)
	{
		if (count != 0)
			list->cur = list->cur->next;
		get_next_streak(list);
		count++;
	}
	count = (count == 0) ? 1 : count;
	return (count);
}

// Cette fonction renvoie la permiere serie de moins de 5. Sinon, renvoie la plus petite serie.

int		skip_seq(t_env *env, t_list *list, int dir)
{
	int count;

	(void)env;
	count = 0;
	while (is_sorted(list->first, list->first->next)) // ATTENTION !! LIRE PLUS BAS
	{
		if (list->id == 1)
			dir == 1 ? ra(env) : rra(env); // ATTENTION !! NEED MODIFIER A CAUSE DE list->first->next INCOMPATIBLE avec dir = 1 !!
		if (list->id == 2)
			dir == 1 ? rb(env) : rrb(env);
		count++;
	}
	if (!is_sorted(list->first, list->first->next))
	{
		if (list->id == 1)
			dir == 1 ? ra(env) : rra(env);
		if (list->id == 2)
			dir == 1 ? rb(env) : rrb(env);
	}
	return (count);
}

void	insert_seq(t_env *env)
{
	int count;

	count = elems_left(env->a_list);
	set_streak(env->a_list, env->a_list->first, env->a_list->dir);
	while (count > 0 && env->b_list->size > 0)
	{
		while (env->b_list->size > 0 && (env->b_list->first->value < env->a_list->first->value || count == 0 || env->a_list->streak == 0))
		{
			pa(env);
			count++;
			env->a_list->streak++;
		}
		while (count > 0 && env->a_list->streak > 0 && env->b_list->first->value >= env->a_list->first->value)
		{
			ra(env);
			count--;
			env->a_list->streak--;
		}
	}
	while (env->a_list->streak > 0)
		ra(env);
}

// on se place au debut de la prochaine suite de nombre.
void	fix_position(t_env *env, t_list *list, int dir)
{
	int cmp;
	int cmp_sign;

	set_streak(list, list->first, dir);
	cmp = list->streak;
	set_streak(list, list->first, -dir);
	cmp_sign = cmp;     // on sauvegarde le signe de cmp.
	cmp = (cmp < 0) ? -cmp : cmp;    // valeur absolue de cmp.
	if ((cmp_sign > 0 && list->streak > 0) || (cmp_sign < 0 && list->streak < 0))
	{
		while (cmp-- >= 0) // si list->first fait partie d'une suite qui le precede, bouge jusqu'a la suivante.
		{
			if (list->id == 1)
				dir < 0 ? rra(env) : ra(env);
			else
				dir < 0 ? rrb(env) : rb(env);
		}
	}
	else
	{
		while (cmp-- > 0 && (list->streak > 1 || list->streak < -1)) // pas bouger si taille de suite passee est < 1
		{
			if (list->id == 1)
				dir < 0 ? rra(env) : ra(env);
			else
				dir < 0 ? rrb(env) : rb(env);
		}
	}
}

void	push_cell(t_env *env, t_list *dest, t_list *src)
{
	int i;

	fix_position(env, dest, 1);
	fix_position(env, src, 1);
	set_streak(src, src->first, 1);
	src->streak = (src->streak) < 0 ? -src->streak : src->streak;
	i = 0;
	while (i++ <= src->streak)
	{
		if (src->id == 1)
			pb(env);
		else
			pa(env);
	}
}

void	merge_cells(t_env *env, t_list *dest, t_list *src)
{
//	fix_position(env, dest, -1);
	set_streak(dest, dest->last, -1);
//	fix_position(env, src, 1);
	set_streak(src, src->first, 1);
	dest->streak = (dest->streak < 0) ? -dest->streak : dest->streak;
	src->streak = (src->streak < 0) ? -src->streak : src->streak;
	printf("dest_streak = %i, src_streak = %i\n", dest->streak, src->streak);
	while (src->streak >= 0 && dest->streak >= 0)
	{
		if(dest->id == 1)
		{
			if (dest->last->value < src->first->value)
			{
				pa(env);
				src->streak--;
			}
			else
			{
				rra(env);
				dest->streak--;
			}
		}
		else
		{
			if(dest->last->value > src->first->value)
			{
				pb(env);
				src->streak--;
			}
			else
			{
				rrb(env);
				dest->streak--;
			}
		}
//		printf("dest_streak = %i, src_streak = %i\n", dest->streak, src->streak);
//		write(1, "lol\n", 4);
	}
	while (dest->streak == -1 && src->streak >= 0)
	{
		if (dest->id == 1)
			pa(env);
		else if (dest->id == 2)
			pb(env);
		src->streak--;
	}
	while (dest->streak-- >= 0)
	{
		if (dest->id == 1)
			ra(env);
		else
			rb(env);
	}
}

void	reverse_seq(t_env *env)
{
	set_streak(env->a_list, env->a_list->first, 1);
	env->a_list->streak = env->a_list->streak < 0 ? -env->a_list->streak : env->a_list->streak;
	while (env->a_list->streak >= 2)
	{
		env->a_list->streak--;
		pb(env);
		if (env->b_list->size > 1)
			rb(env);
	}
	sa(env);
	ra(env);
	ra(env);
	push_cell(env, env->a_list, env->b_list);
//	insert_seq(env);
}

void	push_cells(t_env *env, t_list *dest, t_list *src, int nb)
{
	if (dest->size > 0)
		merge_cells(env, dest, src);
	if (src->size > 0)
	{
		while (nb-- > 0)
			push_cell(env, dest, src);
	}
}

void	atob(t_env *env)
{
	int to_push;

	// Partie 1 - mettre (total_cell / 5 - nombre_de_b_cells) dans b.
	env->a_list->cell_count = count_cells(env->a_list);
	to_push = env->a_list->cell_count / 5;
	to_push = (to_push == 0 && env->a_list->cell_count > 1) ? to_push + 1 : to_push;
	printf("to_push = %i\n", to_push);
	if (env->a_list->size > 0)
		fix_position(env, env->a_list, 1);
	if (env->b_list->size > 0)
		fix_position(env, env->b_list, -1);
	write(1, "PUSH A TO B\n", 12);
	printf("cell_count = %i\n", env->a_list->cell_count);
	push_cells(env, env->b_list, env->a_list, to_push);
	//Partie 2 - merge les listes restantes de a dans celles de b.
	while (env->a_list->cell_count > 1)
	{
		write(1, "MERGE A TO B\n", 13);
		merge_cells(env, env->b_list, env->a_list);
		env->a_list->cell_count--;
	}
}
// MERGE LES DEUX FONCTIONS AVEC UN ARGUMENT DIR !!
void	btoa(t_env *env)
{
	int to_push;

	env->b_list->cell_count = count_cells(env->b_list);
	to_push = env->b_list->cell_count / 5;
	to_push = (to_push == 0 && env->b_list->cell_count > 1) ? to_push + 1 : to_push;
	if (env->b_list->size > 0)
		fix_position(env, env->b_list, 1);  // remplacer par skip_seq()
	if (env->a_list->size > 0)
		fix_position(env, env->a_list, -1);  // remplacer par skip_seq()
	write(1, "PUSH B TO A\n", 12);
	push_cells(env, env->a_list, env->b_list, to_push);
	while (env->b_list->cell_count > 1)
	{
		write(1, "MERGE B TO A\n", 13);
		merge_cells(env, env->a_list, env->b_list);
		env->b_list->cell_count--;
	}
}

void	make_seq(t_env *env)
{
	int count;

	pb(env);
	pb(env);
	if (!is_sorted(env->b_list->first, env->b_list->first->next))
		sb(env);
	pb(env);
	if (!is_sorted(env->b_list->first, env->b_list->first->next))
		env->b_list->first->value > env->b_list->last->value ? rb(env) : sb(env);
	if (!is_sorted(env->a_list->first, env->a_list->first->next))
		sa(env);
	set_streak(env->a_list, env->a_list->first, 1);
	count = env->a_list->streak + 1;
	while (count > 0 && env->b_list->size > 0)
	{
		if (env->b_list->first->value < env->a_list->first->value)
		{
			pa(env);
			count++;
		}
		else
		{
			ra(env);
			count--;
		}
	}
	while (env->b_list->size > 0)
	{
		if (count == 1)
		{
			ra(env);
			count--;
		}
		else if (count == 0)
		{
			pa(env);
			count++;
		}
	}
}

void	sorting_algorithm(t_env *env)
{
	fix_position(env, env->a_list, 1);
	env->a_list->start = env->a_list->first;
	env->a_list->cur = env->a_list->start;
	while (!(is_sorted_list(env, env->a_list) == 0 && env->a_list->size == env->total_numbers)) // true/false inverse. voir plus haut.
	{
		env->a_list->dir = 1;
		get_next_streak(env->a_list);
		while (min_streak(env->a_list, env->a_list->cur) < 4)
		{
			env->a_list->start = env->a_list->first;
			env->a_list->cur = env->a_list->start;
			set_streak(env->a_list, env->a_list->first, env->a_list->dir); // combien d' elements d'affilee sont tries.
			env->a_list->cur = env->a_list->start; 
			if (env->a_list->streak >= 4)                                    // si plus de 5 elements sont tries, on passe la sequence.
				skip_seq(env, env->a_list, 1);
			else if (env->a_list->streak < 4 && env->a_list->streak > -4)
			{
				make_seq(env);  // ATTENTION !! Besoin de check si arrive a start !
				fix_position(env, env->a_list, 1);
			}
			else if (env->a_list->streak <= -4)
			{
				reverse_seq(env);
				fix_position(env, env->a_list, 1);
			}
//			env->a_list->cur = env->a_list->first;
			get_next_streak(env->a_list);
		}
		write(1, "lol\n", 4);
		env->a_list->dir = -1;
		env->b_list->dir = -1;
		if (count_cells(env->a_list) > 1)
		{
//			write(1, "kek1\n", 5);
			atob(env);
			fix_position(env, env->a_list, env->a_list->dir);
		}
		else if (count_cells(env->b_list) > 1)
		{
//			write(1, "kek2\n", 5);
			btoa(env);
			fix_position(env, env->b_list, env->b_list->dir);
		}
		get_next_streak(env->a_list);
	}
	if (count_cells(env->b_list) > 0)
		btoa(env);
	fix_position(env, env->a_list, 1);
}

//////////////////////////////////////
//              MAIN                //
//////////////////////////////////////

void	sort_list(t_env *env)
{
	pb(env);
	pb(env);
	pb(env);
	pb(env);
	pb(env);
}

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
//		fix_position(env, env->a_list, 1);
//		make_seq(env);
//		env->a_list->cur = env->a_list->first;
//		get_next_streak(env->a_list);
//		printf("current = %i\n", env->a_list->cur->value);
//		printf("cell_count = %i\n", count_cells(env->a_list));
//		printf("min_streak = %i\n", min_streak(env->a_list, env->a_list->cur));
//		fix_position(env, env->a_list, 1);
//		skip_seq(env, env->a_list, 1);
//		skip_seq(env, env->a_list, 1);
//		skip_seq(env, env->a_list, 1);
//		env->a_list->cur = env->a_list->first;
//		get_next_streak(env->a_list);
//		printf("current = %i\n", env->a_list->cur->value);
//		reverse_seq(env);
//		set_streak(env->a_list, env->a_list->first, -1);
//		printf("streak = %i\n", env->a_list->streak);
		sort_list(env);
//		fix_position(env, env->b_list, -1);
//		printf("sorted = %i\n", is_sorted_list(env, env->a_list));
//		atob(env);
//		sorting_algorithm(env);
		merge_cells(env, env->b_list, env->a_list);
		write(1, "result : \n", 10);
		print_lists(env);
		destroy_env(env);
	}

	return (0);
}