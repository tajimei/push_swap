/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:17:35 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:55:22 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	parse_int(const char *s, t_state *state)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!ft_isdigit(*s))
		error_exit(state);
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		if (n * sign > 2147483647 || n * sign < -2147483648)
			error_exit(state);
		s++;
	}
	if (*s != '\0')
		error_exit(state);
	return ((int)(n * sign));
}

void	check_duplicate(t_stack *a, int val, t_state *state)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		if (cur->val == val)
			error_exit(state);
		cur = cur->next;
	}
}

t_stack	*new_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->top = NULL;
	stack->size = 0;
	return (stack);
}
