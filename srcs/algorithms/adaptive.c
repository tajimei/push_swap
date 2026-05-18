#include "push_swap.h"

/*
** 適応型ソート：disorderの値に応じて戦略を切り替える
**
** disorder < 0.2  → O(n²)  simple
** disorder < 0.5  → O(n√n) chunk
** disorder >= 0.5 → O(n log n) radix
**
** disorder は init_state後、sort前に compute_disorder() で測定済み
*/
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
