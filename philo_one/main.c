/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:57:24 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/14 15:57:29 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function takes an array of strings and validates them
** @param array of strings
** @return print error and return 1 if argument is invalid or 0 if is valid
*/

int validation(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_digit(av[i][j]))
				return (print_error("not a valid argument"));
			j++;
		}
		i++;
	}
	return (0);
}

/*
** The function initializes the structure
** @param philo = structure, ac = argument count, av = argument vector
** @return 1 if variables is invalid, 0 if allright
*/

int	init_philo(t_philo *philo, int ac, char **av)
{
	if (validation(av))
		return (1);
	if (ft_atoi(av[1]) == LONG_MAX || ft_atoi(av[2]) == LONG_MAX ||
			ft_atoi(av[3]) == LONG_MAX || ft_atoi(av[4]) == LONG_MAX)
		return (print_error("overflow arguments"));
	philo->philo_cnt = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_sleep = ft_atoi(av[3]);
	philo->time_to_eat = ft_atoi(av[4]);
	if (ac == 6)
	{
		if (ft_atoi(av[5]) == LONG_MAX)
			return (print_error("overflow arguments"));
		philo->noteme = ft_atoi(av[5]);
	}
	else
		philo->noteme = 0;
	if (philo->philo_cnt < 2 || philo->philo_cnt > 200)
		return (print_error("invalid number of philosophers"));
	return (0);
}

int main(int ac, char **av)
{
	t_philo philo;

	if (ac < 5 || ac > 6)
		return (print_error("wrong number of arguments"));
	if (init_philo(&philo, ac, av))
		return (1);
	return (0);
}

