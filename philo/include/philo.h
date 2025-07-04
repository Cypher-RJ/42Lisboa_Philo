/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcesar-d <rcesar-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:26:23 by rcesar-d          #+#    #+#             */
/*   Updated: 2025/07/04 13:26:24 by rcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	t_philo			*philos;
	pthread_mutex_t	dead_mutex;
}	t_data;

//! Sintax
int			check_syntax(int argc, char **argv, t_data *data);
int			is_valid_digit_str(const char *str);
int			atoi_positive_lda(const char *str, const char *arg_name, int max);

//! Error
int			arg_error(const char *arg_name, const char *msg);
void		destroy_all(t_data *data);

//! Main
int			main(int ac, char **av);

//! Init
int			init_philos(t_data *data);
int			init_data(t_data *data);

//! Utils
long long	timestamp(void);

//! Sim
void		*philo_routine(void *arg);
int			start_simulation(t_data *data);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

//! Monitor
void		*monitor_routine(void *arg);

//! Sleep
void		precise_sleep(long long ms, t_philo *philo);
int			is_dead(t_data *data);
void		set_dead(t_data *data);

#endif