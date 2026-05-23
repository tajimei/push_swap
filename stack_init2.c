/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_int2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:53:34 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 20:22:08 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_back(t_stack *stack, int val, t_state *state)
{
	t_node	*node;
	t_node	*cur;

	node = new_node(val);
	if (!node)
		error_exit(state);
	if (!stack->top)
	{
		stack->top = node;
	}
	else
	{
		cur = stack->top;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	stack->size++;
}

static void	free_stack(t_stack *stack)
{
	t_node	*cur;
	t_node	*next;

	if (!stack)
		return ;
	cur = stack->top;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(stack);
}

void	free_state(t_state *state)
{
	if (!state)
		return ;
	free_stack(state->a);
	free_stack(state->b);
	free(state);
}

static t_state	*new_state(int bench_mode)
{
	t_state	*state;
	int		i;

	state = malloc(sizeof(t_state));
	if (!state)
		return (NULL);
	state->op_count = 0;
	state->bench_mode = bench_mode;
	state->disorder = 0.0;
	i = 0;
	while (i < 11)
		state->ops[i++] = 0;
	state->a = new_stack();
	state->b = new_stack();
	if (!state->a || !state->b)
		error_exit(state);
	return (state);
}

t_state	*init_state(int argc, char **argv, int bench_mode)
{
	t_state	*state;
	int		i;
	int		val;

	if (argc < 1)
		return (NULL);
	state = new_state(bench_mode);
	if (!state)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		val = parse_int(argv[i], state);
		check_duplicate(state->a, val, state);
		push_back(state->a, val, state);
		i++;
	}
	return (state);
}
