/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:14:57 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 19:14:58 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	t_node	*ci;
	t_node	*cj;
	double	mistakes;
	double	total_pairs;

	if (!a->top || !a->top->next)
		return (0.0);
	mistakes = 0.0;
	total_pairs = 0.0;
	ci = a->top;
	while (ci)
	{
		cj = ci->next;
		while (cj)
		{
			total_pairs += 1.0;
			if (ci->val > cj->val)
				mistakes += 1.0;
			cj = cj->next;
		}
		ci = ci->next;
	}
	return (mistakes / total_pairs);
}
