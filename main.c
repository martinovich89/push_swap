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
	destroy_env(env);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

/////////////////////////////////////
//              UTILS              //
/////////////////////////////////////

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

void	set_elem(t_elem *elem, int nb, void *addr1, void *addr2)
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

int main(int argc, char **argv)
{
	t_env	*env;

	env = create_env();
	if (parse_args(argc, argv, env) != 0)
		ft_error(env, "error message to be provided"); // can use parse_args() return value with some error message array.
	else
	{
		make_lists(env);
		print_lists(env);
		destroy_env(env);
	}

	return (0);
}
