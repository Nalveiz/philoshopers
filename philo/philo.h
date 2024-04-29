/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:48:40 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:25:01 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	struct s_data	*p_data;
	int				id;
	long			last_eat;
	long			meal_eat;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philo;

typedef struct s_data
{
	int				eating;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal;
	int				die_flag;
	long long		t_start;
	int				saturated_philo;
	int				error_flag;
	pthread_mutex_t	dead;
	pthread_mutex_t	meallock;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_data;

int			ft_atoi(const char *str);
int			checker_av(char **av);
int			check_digit(char *av);
int			init_data(t_data *data, int ac, char **av);
int			saturated_philos(t_data *data);
int			ft_die(t_philo *philo);
int			ft_eat(t_philo *philo);
int			ft_wait(t_philo *philo, long long waittime);
int			ft_sleep_and_think(t_philo *philo);

long long	timestamp(void);

void		init_philo(t_data *data);
void		monitor(t_data *data);
void		*routine(void *data);
void		finish_control(t_data *data);
void		close_mutex(t_data *data);
void		full_free(t_data *data);

#endif
