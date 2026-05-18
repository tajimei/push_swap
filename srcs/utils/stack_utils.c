#include "push_swap.h"

/* ========== ノード生成 ========== */

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

/* ========== スタック先頭にpush ========== */

void	push_node(t_stack *stack, t_node *node)
{
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

/* ========== スタック先頭からpop ========== */

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

/* ========== スタック内の最小値 ========== */

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

/* ========== スタック内の最大値 ========== */

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

/* ========== ソート済み判定 ========== */

int	is_sorted(t_stack *stack)
{
	t_node	*cur;

	if (!stack->top)
		return (1);
	cur = stack->top;
	while (cur->next)
	{
		if (cur->val > cur->next->val)
			return (0);
		cur = cur->next;
	}
	return (1);
}

/*
** val がスタック内で何番目に小さいか（0-indexed rank）を返す
** rank変換の補助として使用
*/
int	find_rank(t_stack *stack, int val)
{
	t_node	*cur;
	int		rank;

	rank = 0;
	cur = stack->top;
	while (cur)
	{
		if (cur->val < val)
			rank++;
		cur = cur->next;
	}
	return (rank);
}
