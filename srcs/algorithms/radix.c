#include "push_swap.h"

/* ========== ビット数の計算 ========== */

static int	bit_count(int n)
{
	int	bits;
	int	m;

	bits = 0;
	m = n - 1;
	while (m > 0)
	{
		m >>= 1;
		bits++;
	}
	if (bits == 0)
		bits = 1;
	return (bits);
}

/* ========== radix sort 本体 ========== */

/*
** LSDラディックスソート
**
** スタック操作でLSDを実現する正しい方法:
**   bit=0のパス: aを全部見て
**     ビット0が0 → pbでbへ（bの先頭に積まれる）
**     ビット0が1 → raでaの末尾へ
**   パス終了後: bを全pa（bの先頭から取るので逆順でaに入る）
**
** paで戻すと逆順になる問題を解決するため、
** 「0をpb、1をra」ではなく「1をpb、0をra」に入れ替えて
** 逆順の反転を利用してソート方向を正しく保つ。
**
** つまり:
**   ビットが1 → pbでbへ
**   ビットが0 → raでaの末尾へ
** paで戻すとbの積み順が逆になり、結果的に
** 「小さいrank（bit=0）がaの下部、大きいrank（bit=1）が上部」
** という正しい並びになる。
*/
void	sort_radix(t_state *state)
{
	int	n;
	int	bits;
	int	bit;
	int	i;
	int	b_size;

	if (state->a->size <= 3)
	{
		sort_simple(state);
		return ;
	}
	n = state->a->size;
	bits = bit_count(n);
	bit = 0;
	while (bit < bits)
	{
		i = 0;
		while (i < n)
		{
			if ((state->a->top->rank >> bit) & 1)
				ra(state);
			else
				pb(state);
			i++;
		}
		b_size = state->b->size;
		i = 0;
		while (i < b_size)
		{
			pa(state);
			i++;
		}
		bit++;
	}
}
