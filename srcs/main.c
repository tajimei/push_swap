#include "push_swap.h"

/* ========== フラグ判定ヘルパー ========== */

static int	is_flag(const char *s)
{
	return (s[0] == '-' && s[1] == '-');
}

static int	str_eq(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

/* ========== 戦略セレクター ========== */

/*
** 0: adaptive (default)
** 1: simple
** 2: medium (chunk)
** 3: complex (radix)
*/
static int	parse_strategy(const char *flag)
{
	if (str_eq(flag, "--adaptive"))
		return (0);
	if (str_eq(flag, "--simple"))
		return (1);
	if (str_eq(flag, "--medium"))
		return (2);
	if (str_eq(flag, "--complex"))
		return (3);
	return (-1);
}

/* ========== ソート実行 ========== */

static void	run_sort(t_state *state, int strategy)
{
	const char	*names[4] = {"Adaptive", "Simple", "Chunk", "Radix"};
	const char	*complexities[4] = {
		"O(n log n) / O(n sqrt n) / O(n^2)",
		"O(n^2)",
		"O(n sqrt n)",
		"O(n log n)"
	};

	if (is_sorted(state->a))
		return ;
	state->disorder = compute_disorder(state->a);
	rank_stack(state->a);
	if (strategy == 0)
		sort_adaptive(state);
	else if (strategy == 1)
		sort_simple(state);
	else if (strategy == 2)
		sort_chunk(state);
	else
		sort_radix(state);
	if (state->bench_mode)
		print_bench(state, names[strategy], complexities[strategy]);
}

/* ========== main ========== */

int	main(int argc, char **argv)
{
	t_state	*state;
	int		strategy;
	int		bench_mode;
	int		arg_start;
	int		i;

	if (argc < 2)
		return (0);
	strategy = 0;
	bench_mode = 0;
	arg_start = 1;
	i = 1;
	while (i < argc && is_flag(argv[i]))
	{
		if (str_eq(argv[i], "--bench"))
			bench_mode = 1;
		else
		{
			strategy = parse_strategy(argv[i]);
			if (strategy == -1)
			{
				write(2, "Error\n", 6);
				return (1);
			}
		}
		arg_start++;
		i++;
	}
	if (arg_start >= argc)
		return (0);
	state = init_state(argc - arg_start, argv + arg_start, bench_mode);
	if (!state)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	run_sort(state, strategy);
	free_state(state);
	return (0);
}
