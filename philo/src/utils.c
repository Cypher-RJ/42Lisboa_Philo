#include "../include/philo.h"

int	is_valid_digit_str(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0);
}

int	atoi_positive_limited(const char *str, const char *arg_name, int max)
{
	long long	result;
	int			i;

	if (!is_valid_digit_str(str))
		return (arg_error(arg_name, "must be a positive integer"));

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > max || result > INT_MAX)
			return (arg_error(arg_name, "is too large"));
		i++;
	}
	return ((int)result);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void precise_sleep(long long ms, t_philo *philo)
{
	long long start;
	
	start = timestamp();
	while (!philo->data->dead)
	{
		if (timestamp() - start >= ms)
			break;
		usleep(200);
	}
}

int is_dead(t_data *data)
{
	int dead;
	pthread_mutex_lock(&data->dead_mutex);
	dead = data->dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return dead;
}

void set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_mutex);
}
