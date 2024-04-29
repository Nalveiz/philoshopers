/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:11:26 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:27:07 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *str)
{
	int i;
	int sign;
	int num;
	char *s;

	s = (char *)str;
	i = 0;
	sign = 1;
	num = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == 45 || s[i] == 43)
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] <= '9' && s[i] >= '0')
	{
		num = ((num * 10) + s[i] - 48);
		i++;
	}
	return (num * sign);
}

long long timestamp(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	full_free(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->meallock);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead);
	free(data->forks);
	free(data->philo);
	free(data);
}
