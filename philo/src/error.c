#include "../include/philo.h"

int	arg_error(const char *arg_name, const char *msg)
{
	printf("Error: \"%s\" %s\n", arg_name, msg);
	return (-1);
}

void destroy_all(t_data *data)
{
	int i = 0;

	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->forks);
	free(data->philos);
}
