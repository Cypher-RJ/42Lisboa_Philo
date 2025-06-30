#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_syntax(ac, av, &data))
		return (1);

	if (init_data(&data)) // ou init_forks, init_philos...
		return (1);

	// continua com o resto da simulação
}