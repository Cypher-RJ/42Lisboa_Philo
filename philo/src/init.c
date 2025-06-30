#include "../include/philo.h"

int	init_data(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
	{
		free(data->forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	data->dead = 0;
	data->start_time = timestamp();
	return (0);
}
