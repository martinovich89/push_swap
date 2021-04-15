/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 01:54:21 by mhenry            #+#    #+#             */
/*   Updated: 2021/04/14 01:54:26 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long int	ft_long_atoi(char *str)
{
	int				i;
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	i = ft_skip_space(str);
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void			print_lists(t_env *env)
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

int				is_sorted(t_elem *elem1, t_elem *elem2)
{
	if (elem1->value <= elem2->value)
		return (1);
	else
		return (0);
}

int				is_sorted_list(t_env *env, t_list *list)
{
	int i;

	(void)env;
	list->cur = list->first;
	i = 0;
	while (i < list->size && ((is_sorted(list->cur, list->cur->next) ||
	(list->cur->value == list->max && list->cur->next->value == list->min))))
	{
		list->cur = list->cur->next;
		i++;
	}
	return (i - list->size);
}
