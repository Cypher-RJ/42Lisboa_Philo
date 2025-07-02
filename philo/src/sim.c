#include "../include/philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;
	if (data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&data->print);
		printf("%lld %d has taken a fork\n", timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		// Wait until death
		precise_sleep(data->time_to_die, philo);
		pthread_mutex_unlock(philo->left_fork);
		return NULL;
	}
	if (philo->id % 2 == 0)
		usleep(1000); // Small offset for even philosophers to avoid deadlock
	while (!data->dead && (data->meals_required == -1 || philo->meals < data->meals_required))
	{
		// Pick up forks (start by eating)
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		pthread_mutex_lock(&data->print);
		printf("%lld %d has taken a fork\n", timestamp() - data->start_time, philo->id);
		printf("%lld %d has taken a fork\n", timestamp() - data->start_time, philo->id);
		printf("%lld %d is eating\n", timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = timestamp();
		philo->meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		precise_sleep(data->time_to_eat, philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (data->dead)
			break;
		pthread_mutex_lock(&data->print);
		printf("%lld %d is sleeping\n", timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
		precise_sleep(data->time_to_sleep, philo);
		if (data->dead)
			break;
		pthread_mutex_lock(&data->print);
		printf("%lld %d is thinking\n", timestamp() - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print);
	}
	return NULL;
}

int	start_simulation(t_data *data)
{
	int i;
	pthread_t monitor_thread;

	// Start all philosopher threads
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: failed to create thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}

	// Start monitor thread
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		printf("Error: failed to create monitor thread\n");
		return (1);
	}

	// Wait for monitor to finish
	pthread_join(monitor_thread, NULL);

	// Wait for all philosopher threads to finish
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
