#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!is_dead(data))
	{
		i = 0;
		int all_ate = 1;
		while (i < data->philo_count)
		{
			long long now = timestamp();
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			long long last_meal = data->philos[i].last_meal;
			int meals = data->philos[i].meals;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if ((now - last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(&data->print);
				if (!is_dead(data))
				{
					set_dead(data);
					printf("%lld %d died\n", now - data->start_time, data->philos[i].id);
				}
				pthread_mutex_unlock(&data->print);
				exit(1);
			}
			if (data->meals_required > 0 && meals < data->meals_required)
				all_ate = 0;
			i++;
		}
		if (data->meals_required > 0 && all_ate)
		{
			set_dead(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
