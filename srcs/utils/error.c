#include "push_swap.h"

void	error_exit(t_state *state)
{
	if (state)
		free_state(state);
	write(2, "Error\n", 6);
	exit(1);
}
