/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:18:48 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/23 14:47:51 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_state *state)
{
	if (state->a->size <= 5 || state->disorder < 0.2)
	{
		state->strategy_name = "Adaptive / O(n^2)";
		sort_simple(state);
	}
	else if (state->disorder < 0.5)
	{
		state->strategy_name = "Adaptive / O(n√n)";
		rank_stack(state->a);
		sort_chunk(state);
	}
	else
	{
		state->strategy_name = "Adaptive / O(n log n)";
		rank_stack(state->a);
		sort_radix(state);
	}
}
