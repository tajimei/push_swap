/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:12:12 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:13:52 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*new_node(int val)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->val = val;
	node->rank = 0;
	node->next = NULL;
	return (node);
}

void	push_node(t_stack *stack, t_node *node)
{
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

t_node	*pop_node(t_stack *stack)
{
	t_node	*node;

	if (!stack->top)
		return (NULL);
	node = stack->top;
	stack->top = stack->top->next;
	node->next = NULL;
	stack->size--;
	return (node);
}

int	stack_min(t_stack *stack)
{
	t_node	*cur;
	int		min;

	cur = stack->top;
	min = cur->val;
	while (cur)
	{
		if (cur->val < min)
			min = cur->val;
		cur = cur->next;
	}
	return (min);
}

int	stack_max(t_stack *stack)
{
	t_node	*cur;
	int		max;

	cur = stack->top;
	max = cur->val;
	while (cur)
	{
		if (cur->val > max)
			max = cur->val;
		cur = cur->next;
	}
	return (max);
}
