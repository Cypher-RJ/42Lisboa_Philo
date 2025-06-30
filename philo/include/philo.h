#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;             //! ID do filósofo (de 1 a n)
	int				meals;          //! Número de refeições feitas
	long long		last_meal;      //! Timestamp da última refeição
	pthread_t		thread;         //! Thread do filósofo
	pthread_mutex_t	*left_fork;     //! Ponteiro para o garfo à esquerda
	pthread_mutex_t	*right_fork;    //! Ponteiro para o garfo à direita
	t_data			*data;          //! Ponteiro para dados partilhados
}	t_philo;

typedef struct s_data
{
	int				philo_count;    //! Número total de filósofos
	int				time_to_die;    //! Tempo máximo sem comer (ms)
	int				time_to_eat;    //! Tempo para comer (ms)
	int				time_to_sleep;  //! Tempo para dormir (ms)
	int				meals_required; //! Nº mínimo de refeições (ou -1 se não existir)
	int				dead;           //! Flag: 1 se alguém morreu
	long long		start_time;     //! Timestamp de início da simulação

	pthread_mutex_t	*forks;         //! Array de mutexes (um por garfo)
	pthread_mutex_t	print;          //! Mutex para proteger os prints
	t_philo			*philos;        //! Array de filósofos
}	t_data;

//! Sintax
int	check_syntax(int argc, char **argv, t_data *data);
int	is_valid_digit_str(const char *str);
int	atoi_positive_limited(const char *str, const char *arg_name, int max);

//! Error
int	arg_error(const char *arg_name, const char *msg);

//! Main
int main(int ac, char **av);

#endif