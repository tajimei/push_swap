/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:18:48 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:18:49 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_state *state)
{
	if (state->a->size <= 3)
	{
		sort_simple(state);
		return ;
	}
	if (state->disorder < 0.2)
		sort_simple(state);
	else if (state->disorder < 0.5)
		sort_chunk(state);
	else
		sort_radix(state);
}
