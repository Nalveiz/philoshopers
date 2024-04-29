/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:47:48 by musozer           #+#    #+#             */
/*   Updated: 2024/04/29 19:25:52 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (!(ac == 5 || ac == 6))
		return (write(2, "Wrong arguments number...\n", 26));
	if (checker_av(av) == 1)
		return (write(1, "İnvalid argument value...\n", 26));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (3);
	if (init_data(data, ac, av))
		return (4);
	init_philo(data);
	monitor(data);
	full_free(data);
	return (0);
}
