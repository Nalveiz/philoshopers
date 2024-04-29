/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:30:40 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:26:49 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	saturated_philos(t_data *data)
{
	pthread_mutex_lock(&data->meallock);
	if (data->saturated_philo == data->num_philo)
	{
		pthread_mutex_unlock(&data->meallock);
		return (1);
	}
	pthread_mutex_unlock(&data->meallock);
	return (0);
}

void	close_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		i++;
	}
}

void	finish_control(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->num_philo)
			i = 0;
		pthread_mutex_lock(&data->dead);
		if (timestamp() - data->philo[i].last_eat > data->time_die)
		{
			if (data->die_flag == 0)
				printf("%llu %d %s", timestamp() - data->t_start,
					data->philo[i].id, "is dead\n");
			data->die_flag = 1;
			close_mutex(data);
			pthread_mutex_unlock(&data->dead);
			break ;
		}
		pthread_mutex_unlock(&data->dead);
		if (saturated_philos(data) == 1)
			break ;
		i++;
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_eat = timestamp();
	while (1)
	{
		pthread_mutex_lock(&philo->p_data->meallock);
		if (philo->p_data->saturated_philo == philo->p_data->num_philo)
		{
			pthread_mutex_unlock(&philo->p_data->meallock);
			return (0);
		}
		pthread_mutex_unlock(&philo->p_data->meallock);
		if (ft_die(philo))
			return (0);
		if (ft_eat(philo))
			return (0);
		if (ft_sleep_and_think(philo))
			return (0);
	}
	return (NULL);
}

void	monitor(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = timestamp();
	while (i < data->num_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
		usleep(100);
	}
	finish_control(data);

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
