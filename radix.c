/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:35:08 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/23 17:22:51 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	bit_count(int n)
{
	int	bits;

	bits = 0;
	while (n > 0)
	{
		n >>= 1;
		bits++;
	}
	if (bits == 0)
		bits = 1;
	return (bits);
}

static void	push_and_rotate(t_state *state, int n, int bit)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if ((state->a->top->rank >> bit) & 1)
			ra(state);
		else
			pb(state);
		i++;
	}
}

void	sort_radix(t_state *state)
{
	int	n;
	int	bits;
	int	bit;

	if (state->a->size <= 5)
	{
		sort_simple(state);
		return ;
	}
	n = state->a->size;
	bits = bit_count(n - 1);
	bit = 0;
	while (bit < bits)
	{
		push_and_rotate(state, n, bit);
		while (state->b->size > 0)
			pa(state);
		bit++;
	}
}
