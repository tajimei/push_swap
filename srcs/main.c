/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:36:43 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 20:17:32 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static int	parse_flags(int argc, char **argv,
				int *strategy, int *bench_mode)
{
	int	i;

	i = 1;
	while (i < argc && is_flag(argv[i]))
	{
		if (str_eq(argv[i], "--bench"))
			*bench_mode = 1;
		else
		{
			*strategy = parse_strategy(argv[i]);
			if (*strategy == -1)
				return (-1);
		}
		i++;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	t_state	*state;
	int		strategy;
	int		bench_mode;
	int		arg_start;

	if (argc < 2)
		return (0);
	strategy = 0;
	bench_mode = 0;
	arg_start = parse_flags(argc, argv, &strategy, &bench_mode);
	if (arg_start == -1 || arg_start >= argc)
	{
		if (arg_start == -1)
			write(2, "Error\n", 6);
		return (arg_start == -1);
	}
	state = init_state(argc - arg_start, argv + arg_start, bench_mode);
	if (!state)
		return (write(2, "Error\n", 6), 1);
	run_sort(state, strategy);
	free_state(state);
	return (0);
}
