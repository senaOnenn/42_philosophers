#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

/* ========== STRUCTS ========== */

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	int				someone_died;
	int				all_ate_enough;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/* ========== PROTOTYPES ========== */

/* init.c */
int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
void		cleanup(t_data *data);

/* philo.c */
void		*philo_routine(void *arg);

/* actions.c */
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* monitor.c */
void		*monitor_routine(void *arg);

/* utils.c */
int			ft_atoi(const char *str);
long long	current_time_ms(void);
void		precise_sleep(long long duration_ms, t_data *data);
void		write_status(t_philo *philo, const char *msg);
int			check_sim_status(t_data *data);

#endif