/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:51:06 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:24:16 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	int	i;

	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->saturated_philo = 0;
	data->meal = -1;
	if (ac == 6)
		data->meal = ft_atoi(av[5]);
	data->die_flag = 0;
	data->t_start = 0;
	data->error_flag = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->num_philo));
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->meallock, NULL);
	data->philo = (t_philo *)malloc(sizeof(t_philo) * (data->num_philo));
	if (!data->philo)
		return (2);
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].p_data = data;
		data->philo[i].id = i + 1;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->num_philo];
		pthread_mutex_init(data->philo[i].l_fork, NULL);
		pthread_mutex_init(data->philo[i].r_fork, NULL);
		data->philo[i].last_eat = 0;
		data->philo[i].meal_eat = data->meal;
		data->philo[i].id = i + 1;
		i++;
	}

}



