/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:41:00 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:41:49 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_simple(t_state *state)
{
	int	pos;

	if (state->a->size <= 1)
		return ;
	if (state->a->size == 2)
	{
		sort_two(state);
		return ;
	}
	if (state->a->size == 3)
	{
		sort_three(state);
		return ;
	}
	while (state->a->size > 3)
	{
		pos = min_position(state->a);
		rotate_to_top_a(state, pos);
		pb(state);
	}
	sort_three(state);
	push_all_to_a(state);
}
