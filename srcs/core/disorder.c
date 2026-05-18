#include "push_swap.h"

/*
** スタックaの無秩序度を計算する（0.0 〜 1.0）
** 全ペア中、逆順ペアの割合
** 必ずソート前に呼ぶこと
*/
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
