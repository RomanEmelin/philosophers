/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwinter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:58:44 by mwinter           #+#    #+#             */
/*   Updated: 2021/03/15 13:58:45 by mwinter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int 		philosopher_take_forks(pthread_mutex_t *forks, t_args *args)
{
	int i;

	i = 0;
	while (i < args->philo_cnt)
	{

	}
}

/*
** Function initialize mutex array
** @param mutex array, arguments structure
** @return 1 if init is failed, 0 if success
*/

int			init_forks(pthread_mutex_t *forks, t_args *args)
{
	int i;

	i = 0;
	while (i < args->philo_cnt)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (print_error("can't mutex init.\n"));
		i++;
	}
	return (0);
}

int			initializate_simulation(t_args *args)
{
	//pthread_t philosophers[args->philo_cnt];
	pthread_mutex_t forks[args->philo_cnt];

	if (init_forks(forks, args))
		return (mutex_destroy(forks, args->philo_cnt));
	if (philosophers_take_forks(forks, args))
		return (1);
	return (0);
}