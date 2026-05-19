/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:32:33 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:49:03 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	isqrt(int n)
{
	int	s;

	s = 1;
	while (s * s < n)
		s++;
	return (s);
}

int	in_chunk(t_node *node, int chunk_idx, int chunk_size)
{
	int	lo;
	int	hi;

	lo = chunk_idx * chunk_size;
	hi = lo + chunk_size;
	return (node->rank >= lo && node->rank < hi);
}

void	push_chunk_to_b(t_state *state, int chunk_idx,
	int chunk_size, int chunk_count)
{
	int	pushed;
	int	total;
	int	mid;

	total = chunk_count;
	pushed = 0;
	mid = chunk_idx * chunk_size + chunk_size / 2;
	while (pushed < total)
	{
		if (in_chunk(state->a->top, chunk_idx, chunk_size))
		{
			pb(state);
			if (state->b->top->rank < mid)
				rb(state);
			pushed++;
		}
		else
			ra(state);
	}
}

int	max_rank_pos_b(t_stack *b)
{
	t_node	*cur;
	int		max_rank;
	int		max_pos;
	int		pos;

	cur = b->top;
	max_rank = cur->rank;
	max_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->rank > max_rank)
		{
			max_rank = cur->rank;
			max_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (max_pos);
}

void	rotate_to_top_b(t_state *state, int pos)
{
	int	size;
	int	i;

	size = state->b->size;
	if (pos <= size / 2)
	{
		i = 0;
		while (i < pos)
		{
			rb(state);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size - pos)
		{
			rrb(state);
			i++;
		}
	}
}
