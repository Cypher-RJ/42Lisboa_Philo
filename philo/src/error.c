#include "../include/philo.h"

int	arg_error(const char *arg_name, const char *msg)
{
	printf("Error: \"%s\" %s\n", arg_name, msg);
	return (-1);
}