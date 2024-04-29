/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:45:06 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:20:23 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_wait(t_philo *philo, long long waittime)
{
	long long   tmp;

	tmp = timestamp();
	while (timestamp() - tmp < waittime)
	{
		usleep(200);
		if (ft_die(philo))
			return (1);
	}
	return (0);
}

int	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->p_data->print_mutex);
	if (ft_die(philo))
	{
		pthread_mutex_unlock(&philo->p_data->print_mutex);
		return (1);
	}
	printf("%llu %d %s\n", (timestamp() - philo->p_data->t_start),
			philo->id, status);
	pthread_mutex_unlock(&philo->p_data->print_mutex);
	return (0);
}

int ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->p_data->dead);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&philo->p_data->dead);
	print_status(philo, "is eating");
	if (ft_wait(philo, philo->p_data->time_eat))
		return (1);
	pthread_mutex_lock(&philo->p_data->meallock);
	philo->meal_eat--;
	if (philo->meal_eat == 0)
	{
		philo->p_data->saturated_philo++;
		pthread_mutex_unlock(&philo->p_data->meallock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data->meallock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int ft_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data->meallock);
	if (philo->p_data->saturated_philo == philo->p_data->num_philo)
	{
		pthread_mutex_unlock(&philo->p_data->meallock);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data->meallock);
	pthread_mutex_lock(&philo->p_data->dead);
	if (philo->p_data->die_flag == 1)
	{
		pthread_mutex_unlock(&philo->p_data->dead);
		return (2);
	}
	pthread_mutex_unlock(&philo->p_data->dead);
	return (0);
}

int ft_sleep_and_think(t_philo *philo)
{

	print_status(philo, "is sleeping");

	if (ft_wait(philo, philo->p_data->time_sleep))
		return (1);
	print_status(philo, "is thinking");
	return (0);
}
