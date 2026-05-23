/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtajima <mtajima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:10:51 by mtajima           #+#    #+#             */
/*   Updated: 2026/05/19 20:14:33 by mtajima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_flag(const char *s)
{
	return (s[0] == '-' && s[1] == '-');
}

int	str_eq(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

int	parse_strategy(const char *flag)
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
