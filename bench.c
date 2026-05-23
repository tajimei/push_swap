/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:10:41 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/21 13:43:33 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_uint_fd(unsigned int n, int fd)
{
	char	buf[12];
	int		i;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	i = 11;
	buf[i] = '\0';
	while (n > 0)
	{
		buf[--i] = '0' + (n % 10);
		n /= 10;
	}
	write(fd, buf + i, 11 - i);
}

static void	put_double_2dec_fd(double d, int fd)
{
	unsigned int	integer;
	unsigned int	decimal;

	if (d < 0)
	{
		write(fd, "-", 1);
		d = -d;
	}
	integer = (unsigned int)d;
	decimal = (unsigned int)((d - integer) * 100 + 0.5);
	if (decimal >= 100)
	{
		integer++;
		decimal = 0;
	}
	put_uint_fd(integer, fd);
	write(fd, ".", 1);
	if (decimal < 10)
		write(fd, "0", 1);
	put_uint_fd(decimal, fd);
}

static void	put_str_fd(const char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

static void	print_op_counts(int *ops)
{
	const char	*op_names[11] = {"sa", "sb", "ss", "pa", "pb",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};
	int			i;

	write(2, "[bench] ", 8);
	i = 0;
	while (i < 11)
	{
		put_str_fd(op_names[i], 2);
		write(2, ": ", 2);
		put_uint_fd((unsigned int)ops[i], 2);
		if (i == 4)
			write(2, "\n[bench] ", 9);
		else if (i < 10)
			write(2, "  ", 2);
		i++;
	}
	write (2, "\n", 1);
}

void	print_bench(t_state *state, const char *strategy)
{
	write(2, "[bench] disorder: ", 18);
	put_double_2dec_fd(state->disorder * 100.0, 2);
	write(2, "%\n", 2);
	write(2, "[bench] strategy: ", 18);
	put_str_fd(strategy, 2);
	write(2, "\n", 1);
	write(2, "[bench] total_ops: ", 19);
	put_uint_fd((unsigned int)state->op_count, 2);
	write(2, "\n", 1);
	print_op_counts(state->ops);
}
