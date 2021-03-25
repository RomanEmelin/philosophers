/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 15:57:24 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/21 20:11:26 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** The function takes an array of strings and validates them
** @param array of strings
** @return print error and return 1 if argument is invalid or 0 if is valid
*/

int	validation(char **av)
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

int	init_philo_args(t_args *args, int ac, char **av)
{
	long var[5];

	if (validation(av))
		return (1);
	if (integer_overflow_checker(var, av))
		return (print_error("overflow arguments."));
	args->philo_cnt = var[0];
	args->time_to_die = var[1] + 10;
	args->time_to_eat = var[2];
	args->time_to_sleep = var[3];
	if (ac == 6)
	{
		if ((var[4] = ft_atoi(av[5])) == LONG_MAX)
			return (print_error("overflow arguments."));
		args->meal_cnt = var[4];
	}
	else
		args->meal_cnt = 0;
	if (args->philo_cnt < 2 || args->philo_cnt > 200)
		return (print_error("invalid number of philosophers."));
	args->died = 0;
	args->full = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_args *args;

	if (ac < 5 || ac > 6)
		return (print_error("wrong number of arguments."));
	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
		return (print_error("can't allocate memory for arguments."));
	if (init_philo_args(args, ac, av))
		return (1);
	if (initializate_simulation(args))
		return (1);
	free(args);
	return (0);
}
