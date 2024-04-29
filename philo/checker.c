/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musozer <musozer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:34:36 by musozer           #+#    #+#             */
/*   Updated: 2024/04/22 15:50:09 by musozer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit(char *av)
{
	int	i;

	i = 0;
	while (!av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	checker_av(char **av)
{
	if (check_digit(av[1]) == 1 || ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1)
		return (1);
	if (check_digit(av[2]) == 1 || ft_atoi(av[2]) < 0)
		return (1);
	if (check_digit(av[3]) == 1 || ft_atoi(av[3]) < 0)
		return (1);
	if (check_digit(av[4]) == 1 || ft_atoi(av[4]) < 0)
		return (1);
	if (av[5] && (check_digit(av[5]) == 1 || ft_atoi(av[5]) < 0))
		return (1);
	return (0);
}
