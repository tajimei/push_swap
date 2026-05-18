#include "push_swap.h"

/* ========== √n の計算（整数） ========== */

static int	isqrt(int n)
{
	int	s;

	s = 1;
	while (s * s < n)
		s++;
	return (s);
}

/* ========== aの先頭からchunk_sizeで何番目のチャンクか ========== */

/*
** rank が [chunk_idx * chunk_size, (chunk_idx+1) * chunk_size) に入るか
** chunk_idx: 0-indexed
*/
static int	in_chunk(t_node *node, int chunk_idx, int chunk_size)
{
	int	lo;
	int	hi;

	lo = chunk_idx * chunk_size;
	hi = lo + chunk_size;
	return (node->rank >= lo && node->rank < hi);
}

/* ========== チャンクをbに移す ========== */

/*
** aをぐるぐる回しながら現在のチャンクに属する要素をpb
** chunkの要素を全部bに送るまでループ
** bにpushする際、rankが大きいものは先頭（ra済み）に来るよう工夫:
**   rank が chunk中央より上 → そのままpb（bの先頭へ）
**   rank が chunk中央より下 → pbしてrbでbの底へ
*/
static void	push_chunk_to_b(t_state *state, int chunk_idx,
	int chunk_size, int chunk_count)
{
	int	pushed;
	int	total;
	int	mid;

	total = chunk_count;
	pushed = 0;
	mid = chunk_idx * chunk_size + chunk_size / 2;
	while (pushed < total)
	{
		if (in_chunk(state->a->top, chunk_idx, chunk_size))
		{
			pb(state);
			if (state->b->top->rank < mid)
				rb(state);
			pushed++;
		}
		else
			ra(state);
	}
}

/* ========== bから最大rankをaへ戻す ========== */

/*
** bの中から最大rankのノードを探し、最小コストで先頭に持ってきてpa
*/
static int	max_rank_pos_b(t_stack *b)
{
	t_node	*cur;
	int		max_rank;
	int		max_pos;
	int		pos;

	cur = b->top;
	max_rank = cur->rank;
	max_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->rank > max_rank)
		{
			max_rank = cur->rank;
			max_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (max_pos);
}

static void	rotate_to_top_b(t_state *state, int pos)
{
	int	size;
	int	i;

	size = state->b->size;
	if (pos <= size / 2)
	{
		i = 0;
		while (i < pos)
		{
			rb(state);
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < size - pos)
		{
			rrb(state);
			i++;
		}
	}
}

static void	push_all_b_to_a(t_state *state)
{
	int	pos;

	while (state->b->size > 0)
	{
		pos = max_rank_pos_b(state->b);
		rotate_to_top_b(state, pos);
		pa(state);
	}
}

/* ========== chunk sort 本体 ========== */

void	sort_chunk(t_state *state)
{
	int	n;
	int	chunk_size;
	int	num_chunks;
	int	lo;
	int	hi;
	int	count;
	int	i;

	if (state->a->size <= 3)
	{
		sort_simple(state);
		return ;
	}
	n = state->a->size;
	chunk_size = isqrt(n);
	num_chunks = (n + chunk_size - 1) / chunk_size;
	i = 0;
	while (i < num_chunks)
	{
		lo = i * chunk_size;
		hi = lo + chunk_size;
		if (hi > n)
			hi = n;
		count = hi - lo;
		push_chunk_to_b(state, i, chunk_size, count);
		i++;
	}
	push_all_b_to_a(state);
}
