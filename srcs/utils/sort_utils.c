#include "push_swap.h"

/*
** rank変換：スタックa内の各ノードに0-indexedの順位を付ける
** 例: [3, 1, 4, 2] → rank [2, 0, 3, 1]
** radixソートとchunkソートで必須
*/
void	rank_stack(t_stack *a)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		cur->rank = find_rank(a, cur->val);
		cur = cur->next;
	}
}

/*
** スタック内でrankがtarget_rankのノードが
** 先頭から何番目にあるかを返す（0-indexed）
** 操作コスト計算に使用
*/
int	get_position(t_stack *stack, int target_rank)
{
	t_node	*cur;
	int		pos;

	cur = stack->top;
	pos = 0;
	while (cur)
	{
		if (cur->rank == target_rank)
			return (pos);
		cur = cur->next;
		pos++;
	}
	return (-1);
}
