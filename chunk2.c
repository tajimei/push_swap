/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:46:32 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/23 16:02:20 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_all_b_to_a(t_state *state)
{
	int	pos;

	while (state->b->size > 0)
	{
		pos = max_rank_pos_b(state->b);
		rotate_to_top_b(state, pos);
		pa(state);
	}
}

static void	process_chunk(t_state *state, int i, int chunk_size, int n)
{
	int	lo;
	int	hi;

	lo = i * chunk_size;
	hi = lo + chunk_size;
	if (hi > n)
		hi = n;
	push_chunk_to_b(state, hi, lo);
}

void	sort_chunk(t_state *state)
{
	int	n;
	int	chunk_size;
	int	num_chunks;
	int	i;

	if (state->a->size <= 5)
	{
		sort_simple(state);
		return ;
	}
	n = state->a->size;
	chunk_size = isqrt(n);
	num_chunks = (n + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < num_chunks)
	{
		process_chunk(state, i, chunk_size, n);
		i++;
	}
	push_all_b_to_a(state);
}
