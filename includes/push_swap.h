/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:22:06 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 21:28:12 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				val;
	int				rank;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	int				size;
}					t_stack;

typedef struct s_state
{
	t_stack			*a;
	t_stack			*b;
	int				op_count;
	int				ops[11];
	double			disorder;
	int				bench_mode;
}					t_state;

# define OP_SA 0
# define OP_SB 1
# define OP_SS 2
# define OP_PA 3
# define OP_PB 4
# define OP_RA 5
# define OP_RB 6
# define OP_RR 7
# define OP_RRA 8
# define OP_RRB 9
# define OP_RRR 10

/* ========== stack_init.c ========== */
t_state				*init_state(int argc, char **argv, int bench_mode);
int					ft_isspace(char c);
int					ft_isdigit(char c);
int					parse_int(const char *s, t_state *state);
void				check_duplicate(t_stack *a, int val, t_state *state);
t_stack				*new_stack(void);
void				free_state(t_state *state);

/* ========== operations_a.c ========== */
void				sa(t_state *state);
void				pa(t_state *state);
void				ra(t_state *state);
void				rra(t_state *state);

/* ========== operations_b.c ========== */
void				sb(t_state *state);
void				pb(t_state *state);
void				rb(t_state *state);
void				rrb(t_state *state);

/* ========== operations_ab.c ========== */
void				ss(t_state *state);
void				rr(t_state *state);
void				rrr(t_state *state);

/* ========== disorder.c ========== */
double				compute_disorder(t_stack *a);

/* ========== error.c ========== */
void				error_exit(t_state *state);

/* ========== stack_utils.c ========== */
t_node				*new_node(int val);
void				push_node(t_stack *stack, t_node *node);
t_node				*pop_node(t_stack *stack);
int					stack_min(t_stack *stack);
int					stack_max(t_stack *stack);
int					is_sorted(t_stack *stack);
int					find_rank(t_stack *stack, int val);

/* ========== sort_utils.c ========== */
void				rank_stack(t_stack *a);
int					get_position(t_stack *stack, int rank);

/* ========== str_utils.c ========== */
int					is_flag(const char *s);
int					str_eq(const char *a, const char *b);
int					parse_strategy(const char *flag);

/* ========== algorithms/simple.c ========== */
int					min_position(t_stack *stack);
void				rotate_to_top_a(t_state *state, int pos);
void				push_all_to_a(t_state *state);
void				sort_three(t_state *state);
void				sort_two(t_state *state);
void				sort_simple(t_state *state);

/* ========== algorithms/chunk.c ========== */
int					isqrt(int n);
int					in_chunk(t_node *node, int chunk_idx, int chunk_size);
void				push_chunk_to_b(t_state *state, int chunk_idx,
						int chunk_size, int chunk_count);
int					max_rank_pos_b(t_stack *b);
void				rotate_to_top_b(t_state *state, int pos);
void				sort_chunk(t_state *state);

/* ========== algorithms/radix.c ========== */
void				sort_radix(t_state *state);

/* ========== algorithms/adaptive.c ========== */
void				sort_adaptive(t_state *state);

/* ========== bench.c ========== */
void				print_bench(t_state *state, const char *strategy,
						const char *complexity);

#endif
