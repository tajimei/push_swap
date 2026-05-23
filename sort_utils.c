/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:36:21 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:36:31 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rank_stack(t_stack *a)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		cur->rank = find_rank(a, cur->val);
		cur = cur->next;
	}
}

int	get_position(t_stack *stack, int target_rank)
{
	t_node	*cur;
	int		pos;

	cur = stack->top;
	pos = 0;
	while (cur)
	{
		if (cur->rank == target_rank)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}
