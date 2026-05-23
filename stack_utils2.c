/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:13:14 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:13:42 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*cur;

	if (!stack->top)
		return (1);
	cur = stack->top;
	while (cur->next)
	{
		if (cur->val > cur->next->val)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int	find_rank(t_stack *stack, int val)
{
	t_node	*cur;
	int		rank;

	rank = 0;
	cur = stack->top;
	while (cur)
	{
		if (cur->val < val)
			rank++;
		cur = cur->next;
	}
	return (rank);
}
