#include "../include/philo.h"

int main(int ac, char **av)
{
	t_data data;

	if (check_syntax(ac, av, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (init_philos(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	destroy_all(&data);
	return (0);
}
