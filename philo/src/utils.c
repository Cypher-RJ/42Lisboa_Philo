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
